/*
  Opens and closes the Servo at end of Arm
  if recieves communication at all
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
    myservo.write(160,255,true);        // move the servo to 180, max speed, wait until done
    delay(3000);                                    // write(degrees 0-180, speed 1-255, wait to complete true-false)
    myservo.write(50,255, true);
    delay(1500);// move the servo to 180, slow speed, wait until done
  }
 
} 
