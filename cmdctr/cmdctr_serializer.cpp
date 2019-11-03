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
          bool FlowSwitch;
          uint8_t Servos[NUM_SERVOS];
          uint16_t Thermocouples[NUM_THERMOCOUPLES];
          uint16_t PressureTransducers[NUM_PRESSURE_TRANSDUCERS];

          downlink_data(){
              Servos = new uint8_t[NUM_SERVOS];
              Thermocouples = new uint16_t[NUM_THERMOCOUPLES];
              PressureTransducers = new uint16_t[NUM_PRESSURE_TRANSDUCERS];
          }
          ~downlink_data() {
            if Servos != nullptr {
              delete[] Servos;
            }
            if Thermocouples != nullptr {
              delete[] Thermocouples;
            }
            if PressureTransducers != nullptr {
              delete[] PressureTransducers;
            }
          }
        } ;

        struct uplink_data {
            PropUplinkType Type;
            uint8_t Servos[NUM_SERVOS];

            uplink_data() {
              Servos = new uint8_t[NUM_SERVOS];
            }

            ~uplink_data() {
              if Servos != nullptr {
                delete[] Servos;
              }
            }
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
        uint8_t actual_len = get_verified_length<PropDownlinkMsg>(VerifyPropDownlinkMsgBuffer, GetPropDownlinkMsg, incoming_msg.Payload, incoming_msg.Payload_Size);
        if actual_len == 0 { return nullptr; }
        // Now that we've read a valid message, copy it into the output
        // buffer, then remove it from the input buffer and move
        // everything else down. Then reduce current buffer length by
        // the length of the processed message Then clear the rest of
        // the buffer so that we don't get false positives with the
        // verifiers
        uint8_t actual_msg_buf[actual_len];
        memcpy(actual_msg_buf, incoming_msg.Payload, actual_len);

        const PropDownlinkMsg *actual_msg = GetPropDownlinkMsg(actual_msg_buf);

        struct downlink_data data;
        data.Igniting = actual_msg->Igniting();
        data.LoadCell = actual_msg->LoadCell();
        data.FlowSwitch = actual_msg->FlowSwitch();
        memcpy(data.Servos, actual_msg->Servos()->Data(), actual_msg->Servos()->Data()->size()); //possible room for more efficiency
        memcpy(data.Thermocouples, actual_msg->Thermocouples()->Data(), actual_msg->Thermocouples()->Data()->size());
        memcpy(data.PressureTransducers, actual_msg->PressureTransducers()->Data(), actual_msg->PressureTransducers()->Data()->size());

        return data;
    }
}
