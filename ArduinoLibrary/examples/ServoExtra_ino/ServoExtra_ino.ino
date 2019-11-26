/* Jacob Smith COSI 119A Arm Interfacing Project
  Test program with varspeed servo library
  to show stop function.
*/


//inlcude varSpeedServe library and set up named servos
#include <VarSpeedServo.h>

VarSpeedServo fingerServo;
//set up servo pins
int wait=250;
const int fingerPin = 7;
#define OPEN 160
#define CLOSE 35
//runs once
void setup() {
  //intialize serial connection
  Serial.begin(9600);
  while(!Serial){}
  //attach finger
  fingerServo.attach(fingerPin);
  //display welcome message
  Serial.println("Welcome to Servo Extra Program");
  delay(1000);

}

//runs many times
void loop() {

  Serial.println("Opening and Closing No Stop");
  //fingerServo.detach();
  //fingerServo.attach(fingerPin,OPEN,CLOSE);
  
  fingerServo.write(OPEN, 255, false);
  delay(wait);
  fingerServo.write(CLOSE, 255, false);
  delay(wait*2);

  //wait to make example clearer
  delay(wait*4);

  
  Serial.println("Opening and Closing with Stop");
  fingerServo.write(OPEN, 255, false);
  delay(wait);
  fingerServo.write(CLOSE, 255, false);
  delay(wait/2);
  fingerServo.stop();
  delay(wait/2);

  //wait to make example clearer
  delay(wait*4);

}
