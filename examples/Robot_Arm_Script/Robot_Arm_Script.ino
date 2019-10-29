

/*+
                    This code was written for the Ezzybot Arm MK2 for use in the Brandeis Robotics Lab.

                    The program currently just pushes a button from internal set points.

                    The program needs to have a serial send and receive interface, for connection to the Raspberry Pi

                    
                      This code has been modified by Charlie Squires from code in the following location
                      https://www.robotshop.com/community/robots/show/xyz-positioning-using-arduino-uno-for-6-dof-robotic-arm
                      posted by demej00 10/2/18   modified from code by Oleg Mazurov's most excellent "Robotic Arm Inverse Kinematics on Arduino"

                      Hardware Mods:

  1. The only thing that is required is that your servo turns in the expected directions which could require you to physically reverse the mounting of your servos.
  Go to this page to see the expected servo direction for base, shoulder, elbow, and wrist servos:http://www.micromegacorp.com/downloads/documentation/AN044-Robotic%20Arm.pdf

  2. If you use the sensor shield that I am using you need to do one thing to it: bend the pin that connects the 5v from the shield to the
  Arduino Uno out of the way so that it does not connect to the Uno board.

  You want to use the external voltage on the shield to power only your servos, not the Arduino Uno or it may destroy the Uno,
  I know as I burned up two Uno boards when my external voltage was 6 volts rather than 5.
  This allows you to use higher than 5v to power your servos but if your external voltage is higher than 5 volts then do not connect any 5 volt sensors to the shield or they will be fried.
Issues:

    1. The arm has paulsey
    2. Needs a serial interface to the Raspberry Pi

  R003 used EZZY algorithm
  R004 New class
*******************************************************************************************************/


/*

                                global constants and variables defined


 * **************************************************************************************
*/

#include <VarSpeedServo.h>



/* Arm dimensions( mm ) */

const float BASE_HGT = 100;              //base hight
const float HUMERUS = 140 ;              //shoulder-to-elbow "bone"
const float ELBOW_TO_WRIST = 140;                  //elbow-to-wrist "bone"
const float GRIPPER = 100;              //gripper (incl.heavy duty wrist rotate mechanism) length

#define  ftl(x) ((x)>=0?(long)((x)+0.5):(long)((x)-0.5)) //float to long conversion

/* Servo names/ pin numbers *

*/

const int BAS_SERVO = 12    ;         // Base servo
const int SHL_SERVO = 11   ;          /* Shoulder Servo  */
const int ELB_SERVO = 10  ;           /* Elbow Servo  */
const int WRI_SERVO = 9  ;            /* Wrist servo  */
const int WRO_SERVO = 8 ;             /* Wrist rotate servo  */
const int GRI_SERVO = 7;              /* Gripper servo  */


// Servo offsets
int shoulder_offset = 0;
int elbow_offset = 0;
int wrist_offset = 0;
int base_offset = 0;

/* pre-calculations */

float hum_sq = HUMERUS * HUMERUS;
float elbow_to_wrist_sq = ELBOW_TO_WRIST * ELBOW_TO_WRIST;


int servoSpeed = 15;
/*
   For servo write(value, speed) - speed varies the speed of the move to new position 0=full speed, 1-255 slower to faster
              On the RC-Servos tested, speeds differences above 127 can't be noticed,
               because of the mechanical limits of the servo.

*/


//ServoShield servos; //ServoShield object  assign names to the servo's

VarSpeedServo base_servo, shoulder_servo, elbow_servo, wrist_servo, hand_servo, grip_servo;

int loopCounter = 0;

int pulseWidth = 6.6;

int microsecondsToDegrees;
/*
 * ******************************************** SETUP  executed once ******************************************************
*/
void setup()

{
  Serial.begin(9600);                           // Open serial monitor at 9600 baud to see ping results.

  base_servo.attach( BAS_SERVO );    // attaches a servo to an I/O pin   , 544, 2400
  shoulder_servo.attach( SHL_SERVO );
  elbow_servo.attach( ELB_SERVO );
  wrist_servo.attach( WRI_SERVO );
  hand_servo.attach( WRO_SERVO );
  grip_servo.attach( GRI_SERVO );






  Serial.println("servo park");
  servo_park();    //sets the arm up in a right angle

  delay(3000);

  Serial.println("Start");

}
/*
 * ********************************** LOOP ******************************************************

            set_arm is the key to the arm

 * **********************************************************************************************
*/
void loop()

{

  loopCounter += 1;


  Serial.println("Set Arm 100,200,90,0,10");

  set_arm(100, 200, 90, 0 , servoSpeed); // set_arm(  x point in mm,  y point in mm, base_rotation in degrees,  grip_angle in degrees,  Speed )
  delay(8000);

  Serial.println("Set Arm 340,200,90");

  set_arm( 340, 200, 90, 0 , servoSpeed); //
  delay(8000);



  Serial.println("y y_line");
  // delay(5000);
  y_line();

  //  Serial.println("x  x_line");
  delay(4000);
  x_line();


  //  Serial.println("circle");
  //  circle();

  delay(4000);

  if (loopCounter > 0)
  {

    servo_park();

   delay(5000);

    exit(0);      //pause program - hit reset to continue
  }



}

/*
 * ****************************************************************************************************

                                          SET ARM
                             arm positioning routine utilizing inverse kinematics



 * ***************************************************************************************************
*/

/* arm positioning routine utilizing inverse kinematics *

  x is distance from base mm, y is height mm, base_rotation  is rotation around base in degrees, gripper_angle is hand rottion in degrees, servospeed is how fast is it to happen 0-300

  void set_arm( uint16_t x, uint16_t y, uint16_t z, uint16_t grip_angle )
  *****************************************************************************************************/


void set_arm( float x, float y, int base_rotation_d, int grip_angle_d, int servoSpeed )

{

 
  /* Base angle and radial distance from x,y coordinates */
  /*
     This is the angle of the line shoulder to wrist (S>W) with respect to ground, expressed in radians.
  */

  /*
     radial distance
  */


  /* Wrist position */


  float wrist_y = y - BASE_HGT;        // wrist position y  is this used  spread sheet j9




  float wrist_x = x - GRIPPER;                       //wrist position x   spreadsheet k9
 

  /* Shoulder to wrist distance ( AKA sw ) */

  float s_w = ( wrist_y * wrist_y ) + ( wrist_x * wrist_x );  //s>w

  float s_w_sqrt = sqrt( s_w );                             // S>W spreadsheet I14  shoulder to wrist This is the length of a line between
  // the shoulder and the wrist.
  //If it is longer than the length of the humerus and ulna, then there is no solution.
  

  /* s_w angle to ground */

  float a1 = asin( wrist_y / s_w_sqrt);          // This is the angle of the line S>W with respect to ground, expressed in radians.
  
  /* s_w angle to humerus */

  float a2 = acos((( hum_sq - elbow_to_wrist_sq ) + s_w ) / ( 2 * HUMERUS * s_w_sqrt )); //Spreadsheet called A2 at I16
  //This is the angle of the line S>W with respect to the humerus, expressed in radians

  

  /* shoulder angle ***********************************************/

  float shl_angle_r = 1.571 - a1 - a2;                   // pi - sw wrt gnd - sw to humerus angle
  // spreadsheet  I17

  int shl_angle_dm = 101 + degrees( shl_angle_r ); //This is the required shoulder angle, expressed in degrees. Q17
  int shl_angle_d = degrees( shl_angle_r );    // spreadsheet  J17  modified by Q17  to adjust to servo alignment
  // value should be between 25 and 150
  Serial.print("Shoulder Degrees  ");
  Serial.println(shl_angle_dm);


  /* elbow angle ****************************************************/

  float angle_w = acos(( hum_sq + elbow_to_wrist_sq - s_w ) / ( 2 * HUMERUS * ELBOW_TO_WRIST ));  //This is the required elbow angle, expressed in radians.
  // Spreadsheet I18
  float elb_angle_r = angle_w - shl_angle_r + a1;

  int elb_angle_dm = 0 + degrees( elb_angle_r );      //This is the required elbow angle, expressed in degrees  J18, Q18
                                                     //  int elb_angle_d = degrees( elb_angle_r );
  Serial.print("Elbow Degrees  ");
  Serial.println(elb_angle_dm);
  


  
    /*
   * **********************************

            check limits of positioning and go to set zero if it is not and print out error


  */


  
  bool waits = false;
  int BR = base_rotation_d + base_offset;
  if (BR > 180) BR = 180;
  if (BR < 0) BR = 0;
  base_servo.write(BR, servoSpeed, waits);            // base angle from function call

  int SR = shl_angle_dm + shoulder_offset;
  if (SR > 150) SR = 150;
  if (SR < 25) SR = 25;
  shoulder_servo.write(SR, servoSpeed, waits);          // includes adjust for servo

  int ER = elb_angle_dm + elbow_offset;
  if (ER > 145) ER = 145;
  if (ER < 55) ER = 55;
  elbow_servo.write(ER, servoSpeed, waits);             // includes adj for servo

  // int WR = wri_angle_dm + wrist_offset;
  // if (WR > 180) WR = 180;
  // if (WR < 0) WR = 0;
  //  wrist_servo.write(WR, servoSpeed, waits);

  waits = false;


  Serial.println("base,shoulder,elbow,wrist");
  Serial.print("base rotation ");
  Serial.print(BR);
  Serial.print("           shoulder ");
  Serial.print(SR);
  Serial.print("            elbow  ");
  Serial.print(ER);
  Serial.println("            wrist ");
 

}
/*
 * ****************************************************************************************************


                              move servos to parking position



 * ***************************************************************************************************
*/
/* move servos to parking position */

void servo_park()

{
  Serial.println("servo park");


  base_servo.write(90 + base_offset, servoSpeed);

  shoulder_servo.write(90 + shoulder_offset, servoSpeed);

  elbow_servo.write(90 + elbow_offset, servoSpeed);

  grip_servo.write(80, servoSpeed);

  return;

}


/*
 * ****************************************************************************************************


                             y line



 * ***************************************************************************************************
*/
void y_line()
{
  //int speedtemp = servoSpeed;
  // servoSpeed = 0;

  set_arm( 240, 120, 90, 0 , servoSpeed);
  delay(1000);
  Serial.println(" 240,yaxis,90 ");
  for ( int yaxis = 120; yaxis < 240.0; yaxis += 2 )
  {

    //Serial.print(" yaxis= : "); Serial.println(yaxis);

    set_arm( 240, yaxis, 90, 0 , servoSpeed);

    delay( 50 );

  }

  for ( int yaxis = 240; yaxis > 120; yaxis -= 2 )
  {

    set_arm( 240, yaxis, 100.0, 0 , servoSpeed);

    delay( 50 );

  }
  // servoSpeed = speedtemp;
}

/*
 * ****************************************************************************************************

                                      X line
                              move an arm in a straight line



 * ***************************************************************************************************
*/

/* moves arm in a straight line  alon the x axis*/

void x_line()

{
 
  set_arm(200, 200, 90, 0 , servoSpeed);
  delay(1000);

  for ( int xaxis = 200; xaxis < 340; xaxis += 2 )
  {

    set_arm( xaxis, 200, 90, 0 , servoSpeed);

    delay( 10 );

  }
  delay(1000);
  for ( int xaxis = 340; xaxis > 200.0; xaxis -= 2 )
  {

    set_arm( xaxis, 200, 90, 0 , servoSpeed);

    delay( 50 );

  }

  
}

/*
 * ****************************************************************************************************


                              move the arm in a circle



 * ***************************************************************************************************
*/

void circle()

{
  int speedtemp = servoSpeed;
  servoSpeed = 50;


  const float RADIUS = 130;

 

  float zaxis, yaxis;


  for ( float angle = 0.0; angle < 360.0; angle += 1.0 )
  {

    yaxis = RADIUS * sin( radians( angle )) + 100;

    zaxis = RADIUS * cos( radians( angle )) + 200;

    set_arm( 260, yaxis, zaxis, 0 , 10);

    delay( 100 );

  }
  servoSpeed = speedtemp;
}
