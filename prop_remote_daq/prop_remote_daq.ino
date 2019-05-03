#include <Servo.h> 

Servo servo1;
Servo servo2;
Servo servo3;

#define SERVO_MIN_USEC (900)
#define SERVO_MAX_USEC (2100)
#define SERVO1_PIN (6)
#define SERVO2_PIN (9)
#define SERVO3_PIN (11)
#define IGNITION_PIN (7)
#define IGNITION_TIME_MS (1000)

bool doServoCmd(String);
bool doIgnitionOffCmd(String);
bool doIgniteCmd(String);

String buffer;
bool servosAttached;
void setup() {
    Serial.begin(9600);
    pinMode(IGNITION_PIN, OUTPUT);
    digitalWrite(IGNITION_PIN, 0);

    buffer = "";
    servosAttached = false;
}
void loop() {
    if (Serial.available() > 0) {
        buffer += Serial.readString();
        int eolIndex = buffer.indexOf('\n');
        if (eolIndex != -1) {
            String line = buffer.substring(0, eolIndex);
            buffer = buffer.substring(eolIndex + 1); // to end of buffer

            if (doServoCmd(line)) { }
            else if (doIgnitionOffCmd(line)) { }
            else { doIgniteCmd(line); }
        }
    }
}

bool doServoCmd(String str) {
    // Expects "a###b###c###", where all three numbers are between 0 and 180, inclusive
    if (str.length() != 12) return false;
    if (str.charAt(0) != 'a' || str.charAt(4) != 'b' || str.charAt(8) != 'c') return false;
    int a = str.substring(1,  4).toInt();
    int b = str.substring(5,  8).toInt();
    int c = str.substring(9, 12).toInt();
    // We need to make sure that the servo angles are between 0 and 180
    // But if we read a 0, that could have just been a stoi failure
    // So if we read 0, make sure the text is actually just "000"
    if (a < 0 || a > 180 || (a == 0 && str.substring(1,  4) != "000")) return false;
    if (b < 0 || b > 180 || (b == 0 && str.substring(5,  8) != "000")) return false;
    if (b < 0 || b > 180 || (b == 0 && str.substring(9, 12) != "000")) return false;

    if (!servosAttached) {
      servo1.attach(SERVO1_PIN, SERVO_MIN_USEC, SERVO_MAX_USEC);
      servo2.attach(SERVO2_PIN, SERVO_MIN_USEC, SERVO_MAX_USEC);
      servo3.attach(SERVO3_PIN, SERVO_MIN_USEC, SERVO_MAX_USEC);
    }
    servosAttached = true;
    servo1.write(a);
    servo2.write(b);
    servo3.write(c);

    Serial.print("Servos set to ");
    Serial.print(a);
    Serial.print(" ");
    Serial.print(b);
    Serial.print(" ");
    Serial.print(c);
    Serial.print("\r\n");
    Serial.flush();

    return true;
}
bool doIgnitionOffCmd(String str) {
    // Expects "off"
    if (str == "off") {
        digitalWrite(IGNITION_PIN, 0);
        Serial.print("Turned off.\r\n");
        Serial.flush();
        return true;
    }
    return false;
}
bool doIgniteCmd(String str) {
    // Expects "ignite"
    if (str == "ignite") {
        Serial.print("Igniting!..."); Serial.flush();
        digitalWrite(IGNITION_PIN, 1);
        delay(IGNITION_TIME_MS);
        digitalWrite(IGNITION_PIN, 0);
        Serial.print(" done.\r\n"); Serial.flush();
        return true;
    }
    return false;
}
