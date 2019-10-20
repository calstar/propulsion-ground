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
        const int FLATBUF_BUF_SIZE = 256;
        const uint8_t NUM_SERVOS = 3;
        const uint8_t NUM_THERMOCOUPLES = 3;
        const uint8_t NUM_PRESSURE_TRANSDUCERS = 0;

        uint8_t flatbuf_buffer[FLATBUF_BUF_SIZE];
        unsigned int buffer_len;
// stubbed
    public:
        struct incoming {
          PropDownlinkType Type;
          bool Igniting;
          float LoadCell;
          uint8_t Servos[NUM_SERVOS];
          uint16_t Thermocouples[NUM_THERMOCOUPLES];
          bool FlowSwitch;
          uint16_t PressureTransducers[NUM_PRESSURE_TRANSDUCERS];
        } ;

        struct outgoing {
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

    const PropDownlinkMsg *getPropDownlinkMsg(){
        incoming = getIncomingMsg(flatbuf_buffer, buffer_len);
        payload = incoming->payload();

        const CmdctrIncoming *payload_struct = GetCmdctrIncoming(payload); // Deserialization of payload
        incoming i;
        i.Igniting = payload_struct->;
        i.LoadCell = something;
    }
}
