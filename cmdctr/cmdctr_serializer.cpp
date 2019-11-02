#include "prop_downlink_generated.h"
#include "prop_uplink_generated.h"

#include "mbed.h"
#include "pins.h"

#include "RFM69/RFM69.hpp"
#include "USBSerial.h"
#include <inttypes.h>
#include <string>
#include <unordered_map>
#include <vector>

using namespace flatbuffers;
using namespace Calstar;

class cmdctr_serializer : public msg_ser
{
    private:
        const uint8_t NUM_SERVOS = 3;
        const uint8_t NUM_THERMOCOUPLES = 3;
        const uint8_t NUM_PRESSURE_TRANSDUCERS = 0;

        uint8_t flatbuf_buffer[FLATBUF_BUF_SIZE];
        unsigned int buffer_len;
// stubbed
    public:
        struct downlink_data {
          PropDownlinkType Type;
          bool Igniting;
          float LoadCell;
          uint8_t Servos[NUM_SERVOS];
          uint16_t Thermocouples[NUM_THERMOCOUPLES];
          bool FlowSwitch;
          uint16_t PressureTransducers[NUM_PRESSURE_TRANSDUCERS];
        } ;

        struct uplink_data {
            PropUplinkType Type;
            uint8_t Servos[NUM_SERVOS];
        } ;

    cmdctr_serializer(){
        buffer_len = 0;
    }

    void update_buf(char c){

        if (buffer_len == FLATBUF_BUF_SIZE) {
            // If at end of buffer, shift and add to end
            memmove(buffer, buffer + 1, FLATBUF_BUF_SIZE - 1);
            buffer[FLATBUF_BUF_SIZE - 1] = (uint8_t) c;
        } else {
            // Otherwise build up buffer
            buffer[buffer_len++] = (uint8_t) c;
        }


    }

    /**
    * Returns: a struct downlink_data if flatbuf_buffer contains a valid downlink message.
    **/
    const downlink_data *getPropDownlinkData(){
        msg_data incoming_msg = getIncomingMsg(flatbuf_buffer, buffer_len);
        uint8_t *payload_buf = incoming_msg.payload;

        Verifier verifier(payload_buf, incoming_msg.Payload_Size);
        if (VerifyPropDownlinkMsgBuffer(verifier)) {
            const PropDownlinkMsg *msg = GetPropDownlinkMsg(payload_buf);
            // The message knows how big it should be
            const uint8_t expectedBytes = msg->Bytes();

            uint8_t actual_len = len;
            if (len < expectedBytes) {
                // The verifier will say we have a valid message even if
                // we're a few bytes short Just read more characters at
                // this point by returning early
                return nullptr;
            } else if (len > expectedBytes) {
                // Now we want to verify that the "smaller buffer" with
                // length equal to the expected number of bytes is
                // actually a message in its own right (just a double
                // check basically)
                Verifier smallerVerifier(payload_buf, expectedBytes);
                if (VerifyPropDownlinkMsgBuffer(smallerVerifier)) {
                    // If it is a message, then make sure we use the
                    // correct (smaller) length
                    actual_len = expectedBytes;
                } else {
                    // If it isn't valid, then this buffer just has
                    // some malformed messages... continue and let's
                    // get them out of the buffer by reading more
                    return nullptr;
                }
            }

            // Now that we've read a valid message, copy it into the output
            // buffer, then remove it from the input buffer and move
            // everything else down. Then reduce current buffer length by
            // the length of the processed message Then clear the rest of
            // the buffer so that we don't get false positives with the
            // verifiers
            uint8_t actual_msg_buf[actual_len];
            memcpy(actual_msg_buf, payload_buf, actual_len);
            const PropDownlinkMsg *actual_msg = GetPropDownlinkMsg(actual_msg_buf);
            struct downlink_data data;
            data.Igniting = actual_msg->Igniting();
            data.LoadCell = actual_msg->LoadCell();
            data.FlowSwitch = actual_msg->FlowSwitch();
            flatbuffers::Vector<uint8> servos_vector = actual_msg->Servos();
            servos_len = servos_vector->Length();
            uint8_t servos_buf[servos_len];
            for(i = 0; i < servos_len; i++){
                servos_buf[i] = servos_vector->Get(i);
            }
            data.Servos = servos_buf;
            flatbuffers::Vector<uint8> thermocouples_vector = actual_msg->Thermocouples();
            thermocouples_len = thermocouples_vector->Length();
            uint8_t thermocouples_buf[thermocouples_len];
            for(i = 0; i < thermocouples_len; i++){
                thermocouples_buf[i] = thermocouples_vector->Get(i);
            }
            data.Thermocouples = thermocouples_buf;
            flatbuffers::Vector<uint8> pt_vector = actual_msg->PressureTransducers();
            pt_len = pt_vector->Length();
            uint8_t pt_buf[pt_len];
            for(i = 0; i < pt_len; i++){
                PressureTransducers_buf[i] = pt_vector->Get(i);
            }
            data.PressureTransducers = PressureTransducers_buf;
            return data;
        }
    }
}
