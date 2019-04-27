#include <Servo.h> 

/*
 * To use, first open the Serial Monitor (or a serial interface like PuTTY) on your computer while the Arduino is connected via USB
 * Go to Tools > Serial Monitor
 * While sketch is running, type commands in the format: "[servo number] [angle in degrees]" and press return/Enter
 * to move a servo. Servo numbers should be 1, 2, or 3 labeled on the shield, and angles should generally be in the range 0-180
 * Example:
 * 1 100
 */

Servo servo1;
Servo servo2;
Servo servo3;

#define SERVO_MIN_USEC (870)
#define SERVO_MAX_USEC (2320)
#define SERVO1_PIN (6)
#define SERVO2_PIN (9)
#define SERVO3_PIN (11)

void setup() {
    Serial.begin(9600); 
}
void loop() {
    if (Serial.available() > 0) {
        bool goodData = true;
        // Read the incoming two numbers:
        int servoSelect = Serial.parseInt();
        // Make sure we selected a valid servo
        if (servoSelect < 1 || servoSelect > 3) {
            goodData = false;
            Serial.println("Error: Servo select must be between 1 and 3.");
        }
        int servoAngle = Serial.parseInt();
        if (servoAngle < 0 || servoAngle > 180) {
            goodData = false;
            Serial.println("Error: Servo angle must be between 0 and 180.");
        }
        if (goodData) {
            Serial.print("Setting servo ");
            Serial.print(servoSelect);
            Serial.print(" to angle ");
            Serial.println(servoAngle);

            switch(servoSelect) {
                case 1:
                    if (!servo1.attached()) {
                      servo1.attach(SERVO1_PIN, SERVO_MIN_USEC, SERVO_MAX_USEC);
                    }
                    servo1.write(servoAngle);
                    break;
                case 2:
                    if (!servo2.attached()) {
                      servo2.attach(SERVO2_PIN, SERVO_MIN_USEC, SERVO_MAX_USEC);
                    }
                    servo2.write(servoAngle);
                    break;
                case 3:
                    if (!servo3.attached()) {
                      servo3.attach(SERVO3_PIN, SERVO_MIN_USEC, SERVO_MAX_USEC);
                    }
                    servo3.write(servoAngle);
                    break;
                default: break;
            }
        }
        Serial.readString(); // Flush rest of buffer (usually just \n)
        Serial.flush();
    }
}
