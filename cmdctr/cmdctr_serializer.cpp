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

  uint8_t *flatbuf_buffer;
  unsigned int buffer_len;
  // stubbed
public:
  cmdctr_serializer(bf_len = 0): buffer_len(bf_len) {
    flatbuf_buffer = new uint8_t[FLATBUF_BUF_SIZE];
  }
  ~cmdctr_serializer(){
    if(flatbuf_buffer != nullptr) { delete[] flatbuf_buffer; }
  }
  struct downlink_data {
    bool Igniting;
    float LoadCell;
    bool FlowSwitch;
    uint8_t *Servos;
    uint16_t *Thermocouples;
    uint16_t *PressureTransducers;

    downlink_data(bool igniting, float loadCell, bool flowSwitch, Vector<uint8_t> *servos, Vector<uint16_t> *thermocouples, Vector<uint16_t> *pressureTransducers):
    Igniting(igniting), LoadCell(loadCell), FlowSwitch(flowSwitch) {
      Servos = new uint8_t[servos->size()];
      std::copy(servos.begin(), servos.end(), Servos);
      //memcpy(data.Servos, msg->Servos()->Data(), msg->Servos()->Data()->size());

      Thermocouples = new uint8_t[thermocouples->size()];
      std::copy(thermocouples.begin(), thermocouples.end(), Thermocouples);

      PressureTransducers = new uint8_t[pressureTransducers->size()];
      std::copy(pressureTransducers.begin(), pressureTransducers.end(), PressureTransducers);
    }
    ~downlink_data() {
      if Servos != nullptr { delete[] Servos; }
      if Thermocouples != nullptr { delete[] Thermocouples; }
      if PressureTransducers != nullptr { delete[] PressureTransducers; }
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

  void update_buf(char c){
    if (buffer_len == FLATBUF_BUF_SIZE) {
      // If at end of buffer, shift and add to end
      memmove(flatbuf_buffer, flatbuf_buffer + 1, FLATBUF_BUF_SIZE - 1);
      flatbuf_buffer[FLATBUF_BUF_SIZE - 1] = (uint8_t) c;
    } else {
      // Otherwise build up buffer
      flatbuf_buffer[buffer_len++] = (uint8_t) c;
    }
  }

  /**
  * Returns: a struct downlink_data if flatbuf_buffer contains a valid downlink message.
  **/
  const downlink_data *getPropDownlinkData(){
    msg_data incoming_msg = getIncomingMsg(flatbuf_buffer, buffer_len);
    PropDownlinkMsg *msg = get_specific_msg<PropDownlinkMsg>(VerifyPropDownlinkMsgBuffer, GetPropDownlinkMsg, incoming_msg.Payload, incoming_msg.Payload_Size);
    downlink_data data(msg->Igniting(), msg->LoadCell(), msg->FlowSwitch(), msg->Servos(), msg->Thermocouples(), msg->PressureTransducers());
    return data;
  }
}
