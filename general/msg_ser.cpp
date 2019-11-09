#include "mbed.h"

#include <inttypes.h>
#include <string>
#include <unordered_map>
#include <vector>

using namespace flatbuffers;
using namespace Calstar;

class msg_ser
{
public:
  const static int FLATBUF_BUF_SIZE = 256;
  struct msg_data {
    uint8_t FrameID;
    uint8_t AckReqd;
    uint8_t Bytes;
    uint8_t *Payload;
    uint8_t Payload_Size;
    msg_data(uint8_t fid, uint8_t ack, uint8_t bytes, Vector<uint8_t> *payload):
    FrameID(fid), AckReqd(ack), Bytes(bytes) {
      Payload_Size = payload->size();
      Payload = new uint8_t[Payload_Size];
      std::copy(payload.begin(), payload.end(), Payload);
    }
    ~msg_data() { if (Payload != nullptr) { delete[] Payload; } }
  };

  /**
  * Args: buffer and expected message length in bytes. Received from board-specific deserializers
  * Returns: msg struct. Clears processed message from input buffer
  */
  msg_data* getIncomingMsg(uint8_t input_buffer, unsigned int len) {
    Msg *msg = get_flatbuffer_msg<Msg>(VerifyMsgBuffer, GetMsg, input_buffer, len);
    if (msg == nullptr) {return nullptr; }
    actual_len = msg->Bytes()
    memmove(input_buffer, input_buffer + actual_len, FLATBUF_BUF_SIZE - actual_len);
    len -= actual_len;
    // Clear the rest of the buffer
    memset(input_buffer + len, 0, FLATBUF_BUF_SIZE - len);

    msg_data data(msg->FrameID(), msg->AckReqd(), msg->Bytes(), msg->Payload());
    return data;
  }

  msg* getOutgoingMsg(uint8_t buffer) {

  }

  /**
  * Args:
  <typename T>: type of flatbuffer message being checked. Ex: PropUplinkMsg, PropDownlinkMsg, Msg
  is_valid: Flatbuffer-generated verifier function for this specific message type. Of the form Verify*Buffer
  get_flatbuffer_msg: Flatbuffer-generated function that gets Flatbuffer message from bytes array
  input_buffer: pointer to buffer to be checked for a valid message
  len: length of input_buffer to check for a message
  * Returns:
  *   Verifies message is valid.
  *   If buffer contains valid message, return the valid Flatbuffer Message
      else returns nullptr
  */
  template <typename T>
  uint8_t get_flatbuffer_msg(bool (*is_valid)(Verifier), *T (*get_specific_msg)(*uint8_t), uint8_t *input_buffer, unsigned int len) {
    Verifier verifier(input_buffer, len);
    if (is_valid(verifier)) {
      const T *msg = get_specific_msg(input_buffer);
      // The message knows how big it should be
      const uint8_t expectedBytes = msg->Bytes();

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
        uint8_t smaller_msg_buf[expectedBytes];
        memcpy(smaller_msg_buf, input_buffer, expectedBytes);
        Verifier smallerVerifier(smaller_msg_buf, expectedBytes);
        if (is_valid(smallerVerifier)) {
          // If it is a message, then make sure we use the
          // correct (smaller) length
          return get_specific_msg(smaller_msg_buf);
        } else {
          // If it isn't valid, then this buffer just has
          // some malformed messages... continue and let's
          // get them out of the buffer by reading more
          return nullptr;
        }
      }
    }
  }
}
