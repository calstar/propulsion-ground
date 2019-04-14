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
  myservo_1.attach(6);
  myservo_2.attach(9);
  myservo_3.attach(11);

  //start reading data over serial in
  Serial.begin(9600); 
}

void loop() {

  if (Serial.available() > 0) {
          // read the incoming two numbers:
          servoSelect = Serial.parseInt();
          servoAngle = Serial.parseInt();
          // say what you got:
          Serial.println("I received: ");
          Serial.print("Servo : ");
          Serial.println(servoSelect, DEC);
          Serial.print("Angle: ");
          Serial.println(servoAngle, DEC);
          Serial.println("----");
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
