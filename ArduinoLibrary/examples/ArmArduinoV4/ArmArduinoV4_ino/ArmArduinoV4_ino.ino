/* Jacob Smith COSI 119A Arm Interfacing Project
 *  ArduinoArm Version 4, presents s/e/f/b interface to control the
 *  shoulderm elbor, finger, and base.
 *  Demonstrates control over more of the arm than V3 while still being
 *  simpler than Charile' kinematics program
*/

//inlcude varSpeedServe library and set up named servos
#include <VarSpeedServo.h>

VarSpeedServo shoulderServo;  // create servo object to control a servo
VarSpeedServo elbowServo;
VarSpeedServo fingerServo;
VarSpeedServo baseServo;

//set up servo pins
const int shoulderPin = 10; // the digital pin used for the servo
const int elbowPin = 11;
const int fingerPin = 7;
const int basePin = 12;

//runs once
void setup() {
  //intialize serial connection
  Serial.begin(9600);
  delay(2000);
  //display welcome message
  Serial.println("Welcome to Arm Control");
  Serial.println("Please enter s/e/f/b");
  //attach servos
  shoulderServo.attach(shoulderPin);
  elbowServo.attach(elbowPin);
  fingerServo.attach(fingerPin);
  baseServo.attach(basePin);
}

//runs many times
void loop() {
  //if serial input is detected, move the arm with the given character as input
  if (Serial.available() > 0) {
    moveArm(Serial.read());
  }
  
}

//moves a different part of the arm depending on character paremeter
//prints which part or error
void moveArm(char c){
  if(c=='s'){
    Serial.println("Moving Shoulder");
    moveArmElement(shoulderServo,180,0);
  }else if (c=='e'){
    Serial.println("Moving Elbow");
   moveArmElement(elbowServo,180,0);
  }else if (c=='f'){
    Serial.println("Moving Finger");
    moveArmElement(fingerServo,180,100);
  }else if (c=='b'){
    Serial.println("Moving Base");
    moveArmElement(baseServo,180,0);
  }else if (c!='\n'){
    Serial.println("Error, character command not recognized");
  } 
 }

//moves a servo the specified amount
void moveArmElement(VarSpeedServo element,int startPos, int endPos){
    element.write(startPos,255,true); 
    delay(2000);
    element.write(endPos,255,true); 
    delay(2000);

}
