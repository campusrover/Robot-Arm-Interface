//From https://forum.arduino.cc/index.php?topic=396450
//Modification of link above to tell if receivedchars is a number
//Jacob Smith
// Example 4 - Receive a number as text and convert it to an int

const byte numChars = 32;
char receivedChars[numChars];   // an array to store the received data

boolean newData = false;

int dataNumber = 0;             // new for this version

void setup() {
  Serial.begin(9600);
  Serial.println("<Arduino is ready>");
}

void loop() {
  recvWithEndMarker();
  showNewNumber();
}

void recvWithEndMarker() {
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;

  if (Serial.available() > 0) {
    rc = Serial.read();

    if (rc != endMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    }
    else {
      receivedChars[ndx] = '\0'; // terminate the string
      ndx = 0;
      newData = true;
    }
  }
}

void showNewNumber() {
  if (newData == true) {
    //Serial.println(receivedChars.toInt());
    dataNumber = 0;             // new for this version
    dataNumber = atoi(receivedChars);   // new for this version
    //Serial.print("This just in ... ");
    //Serial.print(receivedChars);
    //Serial.print("Data as Number ... ");    // new for this version
    //Serial.println(dataNumber+3);     // new for this version
    newData = false;

    if (isNumber()) {
       dataNumber = 0;             // new for this version
       dataNumber = atoi(receivedChars);   // new for this version
       Serial.println(dataNumber+5);
    } else {
      Serial.println(receivedChars);
    }
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
