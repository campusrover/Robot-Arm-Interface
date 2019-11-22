/* Jacob Smith COSI 119A Arm Interfacing Project
  Test program with varspeed servo library
  to show limits, stop, and isMoving functions
  These aren't absoultely required to use a servo,
  but ad dmuch more funcitonality
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
  delay(2000);
  //attach finger

  //display welcome message
  Serial.println("Welcome to Servo Extra Program");
  Serial.println(angletoTime(0));
  Serial.println(angletoTime(90));
  Serial.println(angletoTime(180));
  

  //delay(6000);
  fingerServo.attach(fingerPin,angletoTime(CLOSE),angletoTime(OPEN));
  fingerServo.attach(fingerPin);
}

//runs many times
void loop() {
  Serial.println("Opening and Closing Forced");
  //fingerServo.attach(fingerPin);
  fingerServo.write(OPEN, 255, false);
  delay(wait);
  fingerServo.write(CLOSE-10, 255, false);
  delay(wait*2);

  //wait to make example clearer
  delay(wait*4);

  Serial.println("Opening and Closing unForced");
  //fingerServo.detach();
  //fingerServo.attach(fingerPin,OPEN,CLOSE);
  
  fingerServo.write(OPEN, 255, false);
  delay(wait);
  fingerServo.write(CLOSE, 255, false);
  delay(wait*2);

  //wait to make example clearer
  delay(wait*4);

 fingerServo.attach(fingerPin);
  
  /*Serial.println("Stopping Finger in the middle of closing");
  fingerServo.write(OPEN, 255, false);
  delay(wait);
  fingerServo.write(CLOSE, 255, false);
  delay(wait/2);
  fingerServo.stop();
  delay(wait/2);

  //wait to make example clearer
  delay(wait*4);*/

}


int angletoTime(int value){
  int pulse= constrain(value, 0, 180);
  pulse= map(value, 0, 180, 544, 2400);
  return pulse;
}
