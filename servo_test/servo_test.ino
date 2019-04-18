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

void loop() {
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
          servoSelect = Serial.parseInt();
          bool badData = 0;
          //make sure we selected a valid servo
          if (servoSelect != 1 && servoSelect != 2 && servoSelect != 3) {
            badData = 1;
          }
          servoAngle = Serial.parseInt();
          if (servoAngle > 255 || servoAngle < 0) {
            badData = 1;
          }
          Serial.flush();
          if (!badData) {
            // say what you got:
            Serial.println("I received: ");
            Serial.print("Servo : ");
            Serial.println(servoSelect, DEC);
            Serial.print("Angle: ");
            Serial.println(servoAngle, DEC);
            Serial.println("----");
          } else {
            Serial.println("Bad Input");
          }
  }
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
}
