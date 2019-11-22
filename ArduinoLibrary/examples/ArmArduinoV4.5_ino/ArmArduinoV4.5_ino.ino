/* Jacob Smith COSI 119A Arm Interfacing Project
    ArduinoArm Version 4, presents s/e/f/b interface to control the
    shoulderm elbor, finger, and base.
    Demonstrates control over more of the arm than V3 while still being
    simpler than Charile' kinematics program
    Please see //From https://forum.arduino.cc/index.php?topic=396450 for Serial
*/

//data codes
#define NODATA  0
#define NEWWORD 1
#define NEWLINE 2

//inlcude varSpeedServe library and set up named servos
#include <VarSpeedServo.h>
#include <DistanceSensor.h>

DistanceSensor distanceSensor;
VarSpeedServo fingerServo;
//set up servo pins

const int fingerPin = 7;

const byte numChars = 32;
char receivedChars[numChars];   // an array to store the received data
int newData;

//runs once
void setup() {
  //intialize serial connection
  Serial.begin(9600);
  delay(2000);
  //attach finger
  distanceSensor.begin(2, 3);
  fingerServo.attach(fingerPin);
  //display welcome message
  Serial.println("Welcome to Arm Control");
  Serial.println("Enter ARM x y z w MANIP T/F or DIST");
}

//runs many times
void loop() {
  ////if serial input is detected, move the arm with the given character as input
  //if (Serial.available() > 0) {
  // moveManip(Serial.read());
  //}

  recvWithEndMarker();
  process();

}

//moves a different part of the arm depending on character paremeter
//prints which part or error
void moveManip(char c) {
  if (c == 'T') {
    Serial.println("Opening Manipulator");
    fingerServo.write(160, 255, true);
  } else if (c == 'F') {
    Serial.println("Closing Manipulator");
    fingerServo.write(35, 255, true);
  } else if (c == 'R') {
    Serial.println("Reading Distance Sensor");
    Serial.println(distanceSensor.getDistance());
  } else if (c != '\n') {
    Serial.println("Error, character command not recognized");
  }
}

void recvWithEndMarker() {
  static byte ndx = 0;
  char endMarker = ' ';
  char endLineMarker = '\n';
  char rc;

  while (Serial.available() > 0 && newData == NODATA) {
    rc = Serial.read();

    if (rc != endMarker && rc != endLineMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    } else {
      receivedChars[ndx] = '\0'; // terminate the string
      ndx = 0;
      newData = NEWWORD;
    }

    if (rc == endLineMarker) {
      newData = NEWLINE;
    }
  }
}

void process() {
  if(newData==NODATA){
    return;  
  }
  
  checkIfNumber();
  //otherwise, process the request
  if (newData == NEWWORD) {
    Serial.print(":");
  } else if (newData == NEWLINE) {
    Serial.println("");
  }
  newData = NODATA;
}

void checkIfNumber(){
  if (isNumber()) {
       int dataNumber = 0;             // new for this version
       dataNumber = atoi(receivedChars);   // new for this version
       Serial.print(dataNumber+5);
    } else {
      Serial.print(receivedChars);
    }
  }

boolean isNumber() {
  int i = 0;
  char c = receivedChars[i];
  while (c != '\0') {
    if (!isDigit(c)) {  // tests if myChar is a digit
      return false;
    }
    i++;
    c = receivedChars[i];
  }
  return true;
}
