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
    struct msg {
      uint8_t FrameID;
      uint8_t AckReqd;
      uint8_t Bytes;
      uint8_t *Payload;
    } ;

  msg* getIncomingMsg(uint8_t buffer, unsigned int len) {
      Verifier verifier(buffer, len);
      if (VerifyPropDownlinkMsgBuffer(verifier)) {
          const PropDownlinkMsg *msg = GetPropDownlinkMsg(buffer);
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
              Verifier smallerVerifier(buffer, expectedBytes);
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
          memcpy(ret_buf, buffer, actual_len);
          memmove(buffer, buffer + actual_len, FLATBUF_BUF_SIZE - actual_len);
          len -= actual_len;
          // Clear the rest of the buffer
          memset(buffer + len, 0, FLATBUF_BUF_SIZE - len);

          return GetPropDownlinkMsg(ret_buf);
      }
  }

  msg* getOutgoingMsg(uint8_t buffer) {

  }

}
