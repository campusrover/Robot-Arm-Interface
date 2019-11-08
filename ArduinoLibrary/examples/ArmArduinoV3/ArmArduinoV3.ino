/*
  Opens and closes the Servo at end of Arm
 if recieves o or c
*/

#include <VarSpeedServo.h>
char recievedChar;
VarSpeedServo myservo;  // create servo object to control a servo
// a maximum of eight servo objects can be created

const int servoPin = 7; // the digital pin used for the servo

void setup() {
  Serial.begin(9600);
  myservo.attach(servoPin);  // attaches the servo on pin 9 to the servo object
}

void loop() {

  if (Serial.available() > 0) {
    recievedChar = Serial.read();
    moveGripper(recievedChar);
  }

}

void moveGripper(char command) {
  if (command == 'o') {
    Serial.println("Opening Gripper");
    myservo.write(160, 255, true);
  } else if (command == 'c') {
    Serial.println("Closing Gripper");
    myservo.write(50, 255, true);
  } else if (command != '\n') {
    Serial.println("Error, character command not recognized");
  }
}
