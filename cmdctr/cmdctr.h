/*
 * CalSTAR Avionics Ground Station
 *
 * file: gs.h
 *
 * Provides communication between laptop and rocket.
 * Communicates with laptop via UART over USB (with UART with an FTDI cable as
 * backup) Communicates with rocket via radio, 433 MHz Has 2 configurable LEDs
 * and 4 digital inputs on terminal blocks
 *
 * LEDS:
 *  - Rx (PB12)
 *  - Tx (PB13)
 *
 * Digital Inputs:
 *  - IO 1 (PB5)
 *  - IO 2 (PB6)
 *  - IO 3 (PB8) // NOTE: only usable on v3.1+
 *  - IO 4 (PB7)
 */

/***************Includes**********************/
#include "prop_downlink_generated.h"
#include "prop_uplink_generated.h"
#include "json_messages.h"

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

/****************Defines**********************/
#define ENCRYPT_KEY ("CALSTARENCRYPTKE")

#define COMMAND_YES_RETRY ("![YES_RETRY]!")
#define COMMAND_NO_RETRY ("![NO_RETRY]!")

#define LED_ON_TIME_MS (50)

#define RX_BUF_LEN (256)
#define FLATBUF_BUF_SIZE (256)

// resend messages for which have not received acks at 200ms intervals
#define ACK_CHECK_INTERVAL_MS (200)
#define MAX_NUM_RETRIES (50)

#define BATUINT_TO_FLOAT(a) (((float)(a)) / 3308.4751259079328064817304607171f)

// If enabled, turns off other debug printings
#define JSON_LOGGING

/****************Global Variables***************/
DigitalOut rx_led(LED_RX);
DigitalOut tx_led(LED_TX);
DigitalIn io1(IO1);
DigitalIn io2(IO2);
DigitalIn io3(IO3);
DigitalIn io4(IO4);
Timer t;

USBSerial pc;

uint8_t rx_buf[RX_BUF_LEN];
RFM69 radio(SPI1_MOSI, SPI1_MISO, SPI1_SCLK, SPI1_SSEL, RADIO_RST, true);

std::string line = "";
bool retry = true;

int32_t t_tx_led_on;
int32_t t_rx_led_on;
int32_t t_last_resend;

uint8_t frame_id;

uint32_t total_bytes_sent;

// frame_id, <buffer size, buffer, number of retries>
std::unordered_map<uint8_t, std::pair<std::vector<uint8_t>, uint8_t>> acks_remaining;

FlatBufferBuilder builder(FLATBUF_BUF_SIZE);

/***************Function Declarations***********/
void start();
void loop();
bool sendPropUplinkMsg(const std::string &str, bool with_ack);
const PropDownlinkMsg *getPropDownlinkMsgChar(char c);
const PropDownlinkMsg *getPropDownlinkMsg(uint8_t *data, int32_t data_len);
void resend_msgs();
void sendAck(uint8_t frame_id);
void radioTx(const uint8_t *const data, const int32_t data_len);

void sendJsonInt(uint64_t timestamp, const std::string &id, int value);
void sendJsonFloat(uint64_t timestamp, const std::string &id, float value);
void sendJsonString(uint64_t timestamp, const std::string &id, const std::string &value);
void sendJsonLog(const std::string &value);

int main() {
    start();
    while (true) {
        loop();
    }
    return 0;
}

void start() {
    rx_led = 0;
    tx_led = 0;

    radio.reset();
    #ifndef JSON_LOGGING
    pc.printf("![Radio reset complete.]!\r\n");
    #endif

    radio.init();
    radio.setAESEncryption(ENCRYPT_KEY, strlen(ENCRYPT_KEY));

    radio.setHighPowerSettings(true);
    radio.setPowerDBm(20);

    t.start();
    t_tx_led_on = t.read_ms();
    t_rx_led_on = t.read_ms();

    frame_id = 0;

    t_last_resend = t.read_ms();

    // Input button set to internal pull-up
    // It is now active low
    io1.mode(PullUp);

    total_bytes_sent = 0;
}

void loop() {
    if (t.read_ms() - t_last_resend > ACK_CHECK_INTERVAL_MS) {
        resend_msgs();
        t_last_resend = t.read_ms();
    }
    if (tx_led.read() == 1 && t.read_ms() - t_tx_led_on > LED_ON_TIME_MS) {
        tx_led = 0;
    }
    if (rx_led.read() == 1 && t.read_ms() - t_rx_led_on > LED_ON_TIME_MS) {
        rx_led = 0;
    }

    if (pc.readable()) {
        if (!io1) {
            // Button is active-low
            // We want to transmit nothing unless the button pressed
            const char in = pc.getc();
            if (in == '\n') {
                if (line == COMMAND_YES_RETRY) {
                    retry = true;
                    #ifndef JSON_LOGGING
                    pc.printf("%s\r\n", line.c_str());
                    #endif
                } else if (line == COMMAND_NO_RETRY) {
                    retry = false;
                    #ifndef JSON_LOGGING
                    pc.printf("%s\r\n", line.c_str());
                    #endif
                } else {
                    if (retry) {
                        #ifndef JSON_LOGGING
                        pc.printf("![SENDING WITH RETRY '%s', "
                                "bytes: %d]!\r\n",
                                line.c_str(), line.length());
                        #endif
                        line += '\n';
                        tx_led = 1;
                        sendPropUplinkMsg(line, true);
                        t_tx_led_on = t.read_ms();
                        #ifndef JSON_LOGGING
                        pc.printf("\r\nOut of send up link "
                                "message true\r\n");
                        #endif
                    } else {
                        #ifndef JSON_LOGGING
                        pc.printf("![SENDING ONCE ' %s ', "
                                "bytes: %d]!\r\n",
                                line.c_str(), line.length());
                        #endif
                        line += '\n';
                        tx_led = 1;
                        pc.putc('b');
                        sendPropUplinkMsg(line, false);
                        t_tx_led_on = t.read_ms();
                    }
                }
                line = "";
            } else {
                line += in;
            }
        } else {
            if (pc.getc() == '\n') {
                #ifndef JSON_LOGGING
                pc.printf("![TRANSMIT LOCKED]!\r\n");
                #endif
                sendJsonLog("Failed to send frame: Transmit locked.");
            }
        }
    }

    const int32_t num_bytes_rxd = radio.receive((char *)rx_buf, sizeof(rx_buf));
    if (num_bytes_rxd > 1) {
        rx_buf[num_bytes_rxd] = '\0';
        rx_led = 1;
        t_rx_led_on = t.read_ms();
        bool failed = true;
        for (int32_t i = 0; i < num_bytes_rxd - 1; ++i) {
            const PropDownlinkMsg *msg = getPropDownlinkMsgChar(rx_buf[i + 1]);
            if (msg != nullptr) {
                failed = false;
                #ifndef JSON_LOGGING
                pc.printf("![RSSI=%d, bytes: %d]!", radio.getRSSI(), num_bytes_rxd - 1);
                #endif

                sendJsonInt(msg->TimeStamp(), GS_RSSI, radio.getRSSI());

                if (msg->Type() == PropDownlinkType_Ack) {
                    if (acks_remaining.count(msg->FrameID()) == 1) {
                        acks_remaining.erase(msg->FrameID());
                    }
                    #ifndef JSON_LOGGING
                    pc.printf("\r\n");
                    #endif
                } else if (msg->Type() == PropDownlinkType_StateUpdate) {
                    #ifndef JSON_LOGGING
                    pc.printf(
                        "bytes: %d",
                        (int)msg->Bytes());
                    #endif


                    sendJsonInt(msg->TimeStamp(), COMMS_RECD, msg->Bytes());
                    sendJsonInt(msg->TimeStamp(), TPC_STATE, (int)msg->State());
                    sendJsonInt(msg->TimeStamp(), FC_PWRD, (int)msg->FCPowered());
                    sendJsonString(msg->TimeStamp(), TPC_GPS, msg->GPSString()->c_str());
                    sendJsonFloat(msg->TimeStamp(), TPC_BATV, BATUINT_TO_FLOAT(msg->BattVoltage()));

                    if (msg->FCMsg()) {
                        const FCUpdateMsg *fc = msg->FCMsg();

                        sendJsonInt(msg->TimeStamp(), FC_STATE, (int)fc->State());
                        sendJsonFloat(msg->TimeStamp(), FC_ALT, fc->Altitude());

                        #ifndef JSON_LOGGING
                        pc.printf(", ((state: %d, alt: %f, "
                                "bps: %d %d, %d %d, %d %d, %d %d, %d %d, %d %d, %d %d))",
                                (int)fc->State(), fc->Altitude(),
                                (int)fc->BP1Continuity(), (int)fc->BP1Ignited(),
                                (int)fc->BP2Continuity(), (int)fc->BP2Ignited(),
                                (int)fc->BP3Continuity(), (int)fc->BP3Ignited(),
                                (int)fc->BP4Continuity(), (int)fc->BP4Ignited(),
                                (int)fc->BP5Continuity(), (int)fc->BP5Ignited(),
                                (int)fc->BP6Continuity(), (int)fc->BP6Ignited(),
                                (int)fc->BP7Continuity(), (int)fc->BP7Ignited());
                        // pc.printf(", ((state: %d, accel: %f, "
                        //           "%f %f, mag: %f, %f, %f, "
                        //           "gyro: %f, "
                        //           "%f, %f, alt: %f, "
                        //           "pressure: %f, bps: %d %d, "
                        //           "%d %d, %d %d, %d "
                        //           "%d, %d %d, %d %d, %d %d))",
                        //           (int)fc->State(), fc->AccelX(), fc->AccelY(),
                        //           fc->AccelZ(), fc->MagX(), fc->MagY(),
                        //           fc->MagZ(), fc->GyroX(), fc->GyroY(),
                        //           fc->GyroZ(), fc->Altitude(), fc->Pressure(),
                        //           (int)msg->FCMsg()->BP1Continuity(),
                        //           (int)msg->FCMsg()->BP1Ignited(),
                        //           (int)msg->FCMsg()->BP2Continuity(),
                        //           (int)msg->FCMsg()->BP2Ignited(),
                        //           (int)msg->FCMsg()->BP3Continuity(),
                        //           (int)msg->FCMsg()->BP3Ignited(),
                        //           (int)msg->FCMsg()->BP4Continuity(),
                        //           (int)msg->FCMsg()->BP4Ignited(),
                        //           (int)msg->FCMsg()->BP5Continuity(),
                        //           (int)msg->FCMsg()->BP5Ignited(),
                        //           (int)msg->FCMsg()->BP6Continuity(),
                        //           (int)msg->FCMsg()->BP6Ignited(),
                        //           (int)msg->FCMsg()->BP7Continuity(),
                        //           (int)msg->FCMsg()->BP7Ignited());
                        #endif
                    }
                    #ifndef JSON_LOGGING
                    pc.printf("\r\n");
                    #endif
                }
                if (msg->AckReqd()) {
                    sendAck(msg->FrameID());
                }
            } else {
            }
        }
        if (failed) {
            // pc.printf("[!RSSI=%d, bytes: %d]! Failed Flatbuf
            // Deserialize\r\n",
            //           radio.getRSSI(), num_bytes_rxd - 1);
        }
    }
}

bool sendPropUplinkMsg(const std::string &str, bool with_ack) {
    builder.Reset();

    uint8_t servos[3];
    /* NEED TO ACTUALLY PARSE STR */
    if (str[0] == 'a') {
        #ifndef JSON_LOGGING
        pc.printf("%s\r\n", str.c_str());
        #endif
        if(validServoCmd(str)){
            uint8_t angle_a = (uint8_t) std::stoi(str.substr(1,3));
            uint8_t angle_b = (uint8_t) std::stoi(str.substr(5,3));
            uint8_t angle_c = (uint8_t) std::stoi(str.substr(9,3));
            servos[0] = angle_a; servos[1] = angle_b; servos[2] = angle_c;
        }
    }
    else{
            pc.printf("%s is not a valid servo command!\r\n", str.c_str());
        }

    auto servos_offset = builder.CreateVector(servos, sizeof(servos));

    Offset<PropUplinkMsg> msg = CreatePropUplinkMsg(builder, 1, servos_offset, frame_id, with_ack);
    builder.Finish(msg);

    const uint8_t bytes = (uint8_t)builder.GetSize();
    builder.Reset();
    servos_offset = builder.CreateVector(servos, sizeof(servos));
    msg = CreatePropUplinkMsg(builder, bytes, servos_offset, frame_id, with_ack);
    builder.Finish(msg);

    const uint8_t *buf = builder.GetBufferPointer();
    const int32_t size = builder.GetSize();

    if (with_ack) {
        acks_remaining.insert({frame_id, {std::vector<uint8_t>(buf, buf + size), 0}});
    }
    radioTx(buf, size);

    ++frame_id;
}

uint8_t ret_buf[FLATBUF_BUF_SIZE];
const PropDownlinkMsg *getPropDownlinkMsgChar(char c) {
    static uint8_t buffer[FLATBUF_BUF_SIZE];
    static unsigned int len = 0;

    if (len == FLATBUF_BUF_SIZE) {
        // If at end of buffer, shift and add to end
        memmove(buffer, buffer + 1, FLATBUF_BUF_SIZE - 1);
        buffer[FLATBUF_BUF_SIZE - 1] = (uint8_t)c;
    } else {
        // Otherwise build up buffer
        buffer[len++] = (uint8_t)c;
    }

    // The verifier will say that buf has a valid message for any length
    // from actual_length-some number to full buffer length So basically, we
    // trust the verifier, but verify separately by having a #-bytes field
    // in the message itself So if the verifier says there's a valid message
    // in the buffer, we read that message, get the number of bytes that the
    // message says it should be, and actually process a message of THAT
    // size.
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
    return nullptr;
}

void resend_msgs() {
    for (auto &msg : acks_remaining) {
        tx_led = 1;
        #ifndef JSON_LOGGING
        pc.printf("![RESENDING FRAME '%d']!\r\n", (int)msg.first);
        #endif
        const std::vector<uint8_t> &vec = std::get<0>(msg.second);
        radioTx(vec.data(), vec.size());
        std::get<1>(msg.second) = std::get<1>(msg.second) + 1;
        if (std::get<1>(msg.second) >= MAX_NUM_RETRIES) {
            #ifndef JSON_LOGGING
            pc.printf("![FAILED TO SEND FRAME '%d']!\r\n", msg.first);
            #endif
            sendJsonLog("Failed to send frame: Exceeded max number of retries.");
            acks_remaining.erase(msg.first);
        }
    }
    if (tx_led.read() == 1) {
        t_tx_led_on = t.read_ms();
    }
}

// void sendAck(uint8_t frame_id) {
//     builder.Reset();
//     Offset<PropUplinkMsg> ack = CreatePropUplinkMsg(builder, 1, UplinkType_Ack, 0, frame_id, false);
//     builder.Finish(ack);
//     const uint8_t bytes = builder.GetSize();
//     builder.Reset();
//     ack = CreatePropUplinkMsg(builder, bytes, UplinkType_Ack, 0, frame_id, false);
//     builder.Finish(ack);
//     radioTx(builder.GetBufferPointer(), builder.GetSize());
// }


void sendJsonInt(uint64_t timestamp, const std::string &id, int value) {
    pc.printf("{ \"timestamp\": %" PRIu64 ", \"id\": \"%s\", \"value\": %d}\r\n",
        timestamp, id.c_str(), value);
}

void sendJsonFloat(uint64_t timestamp, const std::string &id, float value) {
    pc.printf("{ \"timestamp\": %" PRIu64 ", \"id\": \"%s\", \"value\": %f}\r\n",
        timestamp, id.c_str(), value);
}

void sendJsonString(uint64_t timestamp, const std::string &id, const std::string &value) {
    pc.printf("{ \"timestamp\": %" PRIu64 ", \"id\": \"%s\", \"value\": \"%s\"}\r\n",
        timestamp, id.c_str(), value.c_str());
}

void sendJsonLog(const std::string &value) {
    pc.printf("{\"timestamp\": -1, \"id\": \"%s\", \"value\": \"%s\"}\r\n",
        GS_LOG, value.c_str());
}

void radioTx(const uint8_t *const data, const int32_t data_len) {
    radio.send(data, data_len);
    total_bytes_sent += data_len;
    pc.printf("{ \"timestamp\": -1, \"id\": \"%s\", \"value\": %d}\r\n",
            COMMS_SENT, total_bytes_sent);
}

bool validServoCmd(const std::string &str){
    if (str.length() != 12) return false;
    if (str[0] != 'a' || str[4] != 'b' || str[8] != 'c') return false;
    if (!(std::stoi(str.substr(1,3)) >= 0 && std::stoi(str.substr(1,3)))) <= 360) return false;
    if (!(std::stoi(str.substr(5,3)) >= 0 && std::stoi(str.substr(5,3)))) <= 360) return false;
    if (!(std::stoi(str.substr(9,3)) >= 0 && std::stoi(str.substr(9,3)))) <= 360) return false;
    return true;
}
