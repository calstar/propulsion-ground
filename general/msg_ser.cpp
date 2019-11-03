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
      ~msg_data() {
        if Payload != nullptr {
          delete[] Payload;
        }
      }
    };

/**
* Args: buffer and expected message length in bytes. Received from board-specific deserializers
* Returns: msg struct. Clears processed message from input buffer
*/
  msg_data* getIncomingMsg(uint8_t input_buffer, unsigned int len) {
      uint8_t actual_len = get_verified_length(VerifyMsgBuffer, GetMsg, input_buffer, len);
      if actual_len == 0 { return nullptr; }
      /*
      Verifier verifier(input_buffer, len);
      if (VerifyMsgBuffer(verifier)) {
          const Msg *msg = GetMsg(input_buffer);
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
              Verifier smallerVerifier(input_buffer, expectedBytes);
              if (VerifyMsgBuffer(smallerVerifier)) {
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
          */
          // Now that we've read a valid message, copy it into the output
          // buffer, then remove it from the input buffer and move
          // everything else down. Then reduce current buffer length by
          // the length of the processed message Then clear the rest of
          // the buffer so that we don't get false positives with the
          // verifiers
          uint8_t actual_msg_buf[actual_len];
          memcpy(actual_msg_buf, input_buffer, actual_len);
          memmove(input_buffer, input_buffer + actual_len, FLATBUF_BUF_SIZE - actual_len);
          len -= actual_len;
          // Clear the rest of the buffer
          memset(input_buffer + len, 0, FLATBUF_BUF_SIZE - len);

          const Msg *actual_msg = GetMsg(actual_msg_buf);
          struct msg_data data;
          data.FrameID = actual_msg->FrameID();
          data.AckReqd = actual_msg->AckReqd();
          data.Bytes = actual_msg->Bytes();
          data.Payload = new uint8_t[payload_len];
          return data;
      }
  }

  msg* getOutgoingMsg(uint8_t buffer) {

  }

  /**
  * Args: buffer containing message to be verified, length of message in bytes
  * Returns:
  * Verifies message is valid.
  * If buffer contains valid message, return the actual length of the message
  * If not, return 0
  */
template <typename T>
uint8_t get_verified_length(bool (*is_valid)(Verifier), *T (*get_flatbuffer_msg)(uint8_t), uint8_t input_buffer, unsigned int len) {
  Verifier verifier(input_buffer, len);
  if (is_valid(verifier)) {
      const T *msg = get_flatbuffer_msg(input_buffer);
      // The message knows how big it should be
      const uint8_t expectedBytes = msg->Bytes();

      uint8_t actual_len = len;
      if (len < expectedBytes) {
          // The verifier will say we have a valid message even if
          // we're a few bytes short Just read more characters at
          // this point by returning early
          //return nullptr;
          return 0; // is this equivalent?
      } else if (len > expectedBytes) {
          // Now we want to verify that the "smaller buffer" with
          // length equal to the expected number of bytes is
          // actually a message in its own right (just a double
          // check basically)
          Verifier smallerVerifier(input_buffer, expectedBytes);
          if (is_valid(smallerVerifier)) {
              // If it is a message, then make sure we use the
              // correct (smaller) length
              //actual_len = expectedBytes;
              return expectedBytes;
          } else {
              // If it isn't valid, then this buffer just has
              // some malformed messages... continue and let's
              // get them out of the buffer by reading more
              return 0; // is this equivalent?
          }
      }
  }
}
