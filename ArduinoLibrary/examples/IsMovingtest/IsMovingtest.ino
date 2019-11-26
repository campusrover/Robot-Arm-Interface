/* Jacob Smith COSI 119A Arm Interfacing Project
  Test program with varspeed servo library
  to show limits, stop, and isMoving functions
  These aren't absoultely required to use a servo,
  but ad dmuch more funcitonality
*/


//inlcude varSpeedServe library and set up named servos
#include <VarSpeedServo.h>

VarSpeedServo servo;

//runs once
void setup() {
  //intialize serial connection
  Serial.begin(9600);
  while(!Serial){}
  //attach finger
  //display welcome message
  Serial.println("Welcome to Servo Calibration Program");
  Serial.println("Please Enter Pin of Motor To Test");
    int pinNum;
    while (Serial.available() == 0) {
      pinNum=Serial.parseInt();
    }
   servo.attach(pinNum);
   print("Calibrating Servo at Port",pinNum);

   //set servo to start position
   servo.write(0,255,false);
   delay(2000);
   
   Serial.println("Angle      Number of Times Servo Moved");
   for (int i=1;i<=180;i+=5){
      Serial.print(i);
      Serial.print("\t");
      Serial.println(testWrite(servo,i, 1000)-12);
   
   }
   //move servo to safe position to rest
   servo.write(70,255,false);
   


}

//not used
void loop() {}

void print(String message,int value){
  Serial.print(message);
  Serial.print(":\t");
  Serial.println(value);
}

//returns the number of times the servo moved within the kilTime
int testWrite(VarSpeedServo servo, int value, int killTime){
  servo.write(value,255,false);
  int startTime=millis();
  int elapsedTime;  
  bool withinTime;
  int numMoves=0;
  do{
    //delay(1);
    if(servo.isMoving()){
      numMoves++; 
    }
    elapsedTime = millis()-startTime;
    withinTime=elapsedTime<killTime;
  }while(withinTime);
  return numMoves;
}
