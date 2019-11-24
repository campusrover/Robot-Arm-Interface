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
  //Serial.println(angletoTime(0));
  //Serial.println(angletoTime(90));
  //Serial.println(angletoTime(180));

  fingerServo.attach(fingerPin);
  //initial min and max is 544 2400
  print("Min",fingerServo.getMin());
  print("Max",fingerServo.getMax());
  Serial.println(map(fingerServo.getMin(), 544, 2400, 0, 180));
  Serial.println(map(fingerServo.getMax(), 544, 2400, 0, 180));

  
  /*for (int min=0;min<=180;min+=20){
    Serial.println(min);
    testWrite(fingerServo,min,180,CLOSE-30);
    Serial.println();
  }*/
  delay(500);
  exit(0);
  //fingerServo.attach(fingerPin); 
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

void print(String message,int value){
  Serial.print(message);
  Serial.print(":\t");
  Serial.println(value);
}

int angletoTime(int value){
  int pulse= constrain(value, 0, 180);
  pulse= map(value, 0, 180, 544, 2400);
  return pulse;
}

void testWrite(VarSpeedServo servo,int min, int max, int value){
  servo.attach(fingerPin,angletoTime(min),angletoTime(max));
  print("Min time servo will go",servo.getMin());
  servo.write(value,255,false);
  print("Time Servo is currently going",servo.read());
  delay(1000);
}
