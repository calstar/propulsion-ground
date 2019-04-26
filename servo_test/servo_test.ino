#include <Servo.h> 

//initialize each servo
Servo myservo_1;
Servo myservo_2;
Servo myservo_3;

//initialize variables for input over serial
uint8_t servoSelect = 0;
uint8_t servoAngle = 0;

void setup() {

  //map servo objects to pins on Arduino
  //attach(pin, min pulse width in usec, max pulse width in usec)
  myservo_1.attach(6,870,2320);
  myservo_2.attach(9,870,2320);
  myservo_3.attach(11,870,2320);
  //start reading data over serial in
  Serial.begin(9600); 
}


/**
 * To use, first open the Serial Monitor on your computer while the Arduino is connected via USB
 * Go to Tools > Serial Monitor
 * While sketch is running, type commands in the format: [servo number] [angle in degrees] and press return/Enter
 * to move a servo. Servo numbers should be 1, 2, or 3 labeled on the shield, and angles should generally be in the range 60-190
 * Example:
 * 1 100
 *  I received: 
    00:22:38.532 -> Servo : 1
    00:22:38.532 -> Angle: 100
    00:22:38.579 -> ----
    00:22:38.579 -> Servo 1 to angle: 100
 */
void loop() {
  // Uncomment the following to have the servos automatically move, for testing only
  //  myservo_1.write(80);
  //  delay(500);
  //  myservo_2.write(80);
  //  delay(500);
  //  myservo_3.write(80);
  //  delay(500);
  //  myservo_1.write(170);
  //  delay(500);
  //  myservo_2.write(170);
  //  delay(500);
  //  myservo_3.write(170);
  //  delay(500);
  if (Serial.available() > 0) {
          // read the incoming two numbers:
          uint8_t servoSelect = Serial.parseInt();
          bool goodData = true;
          //make sure we selected a valid servo
          if (servoSelect != 1 && servoSelect != 2 && servoSelect != 3) {
            goodData = false;
          }
          uint8_t servoAngle = Serial.parseInt();
          if (servoAngle > 255 || servoAngle < 0) {
            goodData = false;
          }
          Serial.flush();
          if (goodData) {
            // say what you got:
            Serial.println("I received: ");
            Serial.print("Servo : ");
            Serial.println(servoSelect, DEC);
            Serial.print("Angle: ");
            Serial.println(servoAngle, DEC);
            Serial.println("----");
  
            switch(servoSelect) {
              case 1:
                myservo_1.write(servoAngle);
                Serial.print("Servo 1 to angle: ");
                Serial.println(servoAngle, DEC);
                break;
              case 2:
                myservo_2.write(servoAngle);
                Serial.print("Servo 2 to angle: ");
                Serial.println(servoAngle, DEC);
                break;
              case 3:
                myservo_3.write(servoAngle);
                Serial.print("Servo 3 to angle: ");
                Serial.println(servoAngle, DEC);
                break;
              default:
                break;
            }
          } else {
            Serial.println("Bad Input");
          }
  }

}
