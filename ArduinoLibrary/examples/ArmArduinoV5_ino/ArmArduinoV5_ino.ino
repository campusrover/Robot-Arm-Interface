/* Jacob Smith COSI 119A Arm Interfacing Project
    ArduinoArm Version 4, presents s/e/f/b interface to control the
    shoulderm elbor, finger, and base.
    Demonstrates control over more of the arm than V3 while still being
    simpler than Charile' kinematics program
    Please see //From https://forum.arduino.cc/index.php?topic=396450 for Serial
*/

//data codes
#define NODATA    0
#define FIRSTWORD 1
#define NUMBER    2
#define NEWLINE   3

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
boolean firstWord = true;

//runs once
void setup() {
  //intialize serial connection
  Serial.begin(9600);
  while(!Serial){}
  //attach finger
  distanceSensor.begin(2, 3);
  fingerServo.attach(fingerPin);
  //display welcome message
  Serial.println("Welcome to Arm Control");
  Serial.println("Enter ARM x y z w MANIP 1/0");
}

//runs many times
void loop() {

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

  boolean foundWord = false;

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
      foundWord = true;
    }


    if (rc == endLineMarker && !firstWord) {
      newData = NEWLINE;
    } else if (rc==endLineMarker && firstWord){
      newData= FIRSTWORD;
    }else if (foundWord && firstWord) {
      newData = FIRSTWORD;
      firstWord=false;
    } else if (foundWord && !firstWord) {
      newData = NUMBER;
    }
  }
}

void process() {
  if (newData == NODATA) {
    return;
  }

  //Serial.print("FLAG:");
   // Serial.println(newData);

  //otherwise, process the request
  if (newData == FIRSTWORD) {
    if(strcmp(receivedChars, "ARM")==0){
       Serial.println("PP");
    }
    Serial.print(receivedChars);
  } else if (newData == NUMBER | newData == NEWLINE) {
    Serial.print(":");
    int dataNumber = 0;             // new for this version
    dataNumber = atoi(receivedChars);   // new for this version
    Serial.print(dataNumber + 5);
   
  }

  if (newData == NEWLINE) {
    Serial.println("");
  }
  newData = NODATA;
  firstWord=true;
}
