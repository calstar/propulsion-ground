/*
 * CalSTAR Avionics Ground Station
 *
 * file: cmdctr.h
 *
 * Provides communication between laptop and ground propulsion test setup.
 * Communicates with laptop via UART over USB (with UART with an FTDI cable as
 * backup) Communicates with ground propulsion test setup via radio, 433 MHz
 * Has 2 configurable LEDs and 4 digital inputs on terminal blocks
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

/****************Global Variables***************/
DigitalOut rx_led(LED_RX);
DigitalOut tx_led(LED_TX);
DigitalOut tx_lock(IO2); // using for tx lock led
DigitalIn io1(IO1);
// DigitalIn io2(IO2);
DigitalIn io3(IO3);
DigitalIn io4(IO4);
Timer t;

//USBSerial pc;
Serial pc(DEBUG_TX, DEBUG_RX, 115200);

uint8_t rx_buf[RX_BUF_LEN];
RFM69 radio(SPI1_MOSI, SPI1_MISO, SPI1_SCLK, SPI1_SSEL, RADIO_RST, true);

std::string line = "";
bool retry = true;

int32_t t_tx_led_on;
int32_t t_rx_led_on;
int32_t t_last_resend;

uint8_t frame_id;

// frame_id, <buffer size, buffer, number of retries>
std::unordered_map<uint8_t, std::pair<std::vector<uint8_t>, uint8_t>> acks_remaining;

FlatBufferBuilder builder(FLATBUF_BUF_SIZE);

/***************Function Declarations***********/
void start();
void loop();
bool sendPropUplinkMsg(const std::string &str, bool with_ack);
const PropDownlinkMsg *getPropDownlinkMsgChar(char c);
void resend_msgs();
void sendAck(uint8_t frame_id);
void radioTx(const uint8_t *const data, const int32_t data_len);

bool validServoCmd(const std::string &str);
bool validIgnitionOffCmd(const std::string &str);
bool validIgnitionCmd(const std::string &str);
bool advertised = false;

int main() {
    start();
    while (true) {
        loop();
    }
    return 0;
}

void start() {
    //To be replaced with USBSerial once it has been debugged for Mbed-5.15
    //pc.baud(115200);
    pc.set_blocking(false);

    rx_led = 0;
    tx_led = 0;
    tx_lock = 0;

    radio.reset();
    pc.printf("{\"status\":\"radio reset\"}\r\n");

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
    tx_lock = io1 ? 0 : 1;
    
    if(acks_remaining.size() == 0 && !advertised){
        pc.printf("\rEnter Command: ");
        advertised = true;
    }
    if (pc.readable()) {
        const char in = pc.getc();
        if (in == '\n' || in == '\r') {
            if (line == COMMAND_YES_RETRY) {
                retry = true;
                pc.printf("{\"status\":\"retry on\"}\r\n");
            } else if (line == COMMAND_NO_RETRY) {
                retry = false;
                pc.printf("{\"status\":\"retry off\"}\r\n");
            } else {
                tx_led = 1;
                sendPropUplinkMsg(line, retry);
                advertised = false;
                t_tx_led_on = t.read_ms();
            }
            line = "";
        } else {
            pc.putc(in);
            line += in;
        }
    }

    const int32_t num_bytes_rxd = radio.receive((char *)rx_buf, sizeof(rx_buf));
    if (num_bytes_rxd > 1) {
        rx_buf[num_bytes_rxd] = '\0';
        rx_led = 1;
        t_rx_led_on = t.read_ms();
        for (int32_t i = 0; i < num_bytes_rxd - 1; ++i) {
            const PropDownlinkMsg *msg = getPropDownlinkMsgChar(rx_buf[i + 1]);
            if (msg != nullptr) {
                if (msg->Type() == PropDownlinkType_Ack) {
                    if (acks_remaining.count(msg->FrameID()) == 1) {
                        acks_remaining.erase(msg->FrameID());
                    }
                } else if (msg->Type() == PropDownlinkType_StateUpdate) {
                    bool igniting = msg->Igniting();
                    float loadCell = msg->LoadCell();
                    const Vector<uint8_t> *servos = msg->Servos();
                    int servosLen = servos->size() / sizeof(uint8_t);
                    const Vector<uint16_t> *thermocouples = msg->Thermocouples();
                    int thermocouplesLen = thermocouples->size() / sizeof(uint16_t);
                    bool flowSwitch = msg->FlowSwitch();
                    const Vector<uint16_t> *pressureTransducers = msg->PressureTransducers();
                    int pressureTransducersLen = pressureTransducers->size() / sizeof(uint16_t);

                    std::string ignitingStr = igniting ? "true" : "false";
                    std::string loadCellStr = "null"; // TODO: output float
                    std::string servosStr = "[";
                    for (int i = 0; i < servosLen; i++) {
                        servosStr += std::to_string(servos->Get(i));
                        if (i < servosLen - 1) {
                            servosStr += ",";
                        }
                    }
                    servosStr += "]";
                    std::string thermocouplesStr = "[";
                    for (int i = 0; i < thermocouplesLen; i++) {
                        thermocouplesStr += std::to_string(thermocouples->Get(i));
                        if (i < thermocouplesLen - 1) {
                            thermocouplesStr += ",";
                        }
                    }
                    thermocouplesStr += "]";
                    std::string flowSwitchStr = flowSwitch ? "true" : "false";
                    std::string pressureTransducersStr = "[";
                    for (int i = 0; i < pressureTransducersLen; i++) {
                        pressureTransducersStr += std::to_string(pressureTransducers->Get(i));
                        if (i < pressureTransducersLen - 1) {
                            pressureTransducersStr += ",";
                        }
                    }
                    pressureTransducersStr += "]";

                    pc.printf("{\"update\":{\"igniting\":%s,\"loadCell\":%s,\"servos\":%s,\"thermocouples\":%s,\"flowSwitch\":%s,\"pressureTransducers\":%s}}\r\n",
                        ignitingStr.c_str(), loadCellStr.c_str(), servosStr.c_str(), thermocouplesStr.c_str(), flowSwitchStr.c_str(), pressureTransducersStr.c_str());
                }
                if (msg->AckReqd()) {
                    sendAck(msg->FrameID());
                }
            }
        }
    }
}

bool sendPropUplinkMsg(const std::string &str, bool with_ack) {
    builder.Reset();

    PropUplinkType type;
    uint8_t servos[3];
    if (validServoCmd(str)) {
        type = PropUplinkType_Servos;
        servos[0] = (uint8_t)std::stoi(str.substr(1,3));
        servos[1] = (uint8_t)std::stoi(str.substr(5,3));
        servos[2] = (uint8_t)std::stoi(str.substr(9,3));
        pc.printf("{\"status\":\"sending servo command (%d,%d,%d)\"}\r\n", servos[0], servos[1], servos[2]);
    } else if (validIgnitionOffCmd(str)) {
        type = PropUplinkType_IgnitionOff;
        pc.printf("{\"status\":\"sending ignition off command\"}\r\n");
    } else if (validIgnitionCmd(str)) {
        if (!io1) {
            // Button is active-low, so it's currently pressed and we can send ignition
            type = PropUplinkType_Ignition;
            pc.printf("{\"status\":\"sending ignition pulse command\"}\r\n");
        } else {
            // Button not pressed
            pc.printf("{\"status\":\"transmission of ignition command is locked\"}\r\n");
            return false;
        }
    } else {
        pc.printf("{\"status\":\"'%s' invalid\"}\r\n", str.c_str());
        return false;
    }

    auto servos_offset = type == PropUplinkType_Servos ? builder.CreateVector(servos, sizeof(servos)) : 0;

    Offset<PropUplinkMsg> msg = CreatePropUplinkMsg(builder, 1, frame_id, with_ack, type, servos_offset);
    builder.Finish(msg);

    const uint8_t bytes = (uint8_t)builder.GetSize();
    builder.Reset();
    servos_offset = type == PropUplinkType_Servos ? builder.CreateVector(servos, sizeof(servos)) : 0;
    msg = CreatePropUplinkMsg(builder, bytes, frame_id, with_ack, type, servos_offset);
    builder.Finish(msg);

    const uint8_t *buf = builder.GetBufferPointer();
    const int32_t size = builder.GetSize();

    if (with_ack) {
        acks_remaining.insert({frame_id, {std::vector<uint8_t>(buf, buf + size), 0}});
    }
    radioTx(buf, size);

    ++frame_id;

    return true;
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
        const std::vector<uint8_t> &vec = std::get<0>(msg.second);
        pc.printf("Resending Message: %d\n", msg.first);
        radioTx(vec.data(), vec.size());
        std::get<1>(msg.second) = std::get<1>(msg.second) + 1;
        if (std::get<1>(msg.second) >= MAX_NUM_RETRIES) {
            pc.printf("{\"status\":\"Failed to send frame: Exceeded max number of retries.\"}\r\n");
            acks_remaining.erase(msg.first);
        }
    }
    if (tx_led.read() == 1) {
        t_tx_led_on = t.read_ms();
    }
}

void sendAck(uint8_t frame_id) {
    builder.Reset();
    Offset<PropUplinkMsg> ack = CreatePropUplinkMsg(builder, 1, frame_id, false, PropUplinkType_Ack, 0);
    builder.Finish(ack);
    const uint8_t bytes = builder.GetSize();
    builder.Reset();
    ack = CreatePropUplinkMsg(builder, bytes, frame_id, false, PropUplinkType_Ack, 0);
    builder.Finish(ack);
    radioTx(builder.GetBufferPointer(), builder.GetSize());
}


void radioTx(const uint8_t *const data, const int32_t data_len) {
    radio.send(data, data_len);
    pc.printf("{\"status\":\"Sending %d bytes\"}\r\n", data_len);
    // WARNING: Only works because payloads are fewer bytes than max radio can send at once (~64)
}

bool validServoCmd(const std::string &str) {
    // Expects "a###b###c###", where all three numbers are between 0 and 180, inclusive
    if (str.length() != 12) return false;
    if (str[0] != 'a' || str[4] != 'b' || str[8] != 'c') return false;
    int a = std::stoi(str.substr(1,3));
    int b = std::stoi(str.substr(5,3));
    int c = std::stoi(str.substr(9,3));
    // We need to make sure that the servo angles are between 0 and 180
    // But if we read a 0, that could have just been a stoi failure
    // So if we read 0, make sure the text is actually just "000"
    if (a < 0 || a > 180 || (a == 0 && str.substr(1,3) != "000")) return false;
    if (b < 0 || b > 180 || (b == 0 && str.substr(5,3) != "000")) return false;
    if (c < 0 || c > 180 || (c == 0 && str.substr(9,3) != "000")) return false;
    return true;
}
bool validIgnitionOffCmd(const std::string &str) {
    // Expects "off"
    return str == "off";
}
bool validIgnitionCmd(const std::string &str) {
    // Expects "ignite"
    return str == "ignite";
}