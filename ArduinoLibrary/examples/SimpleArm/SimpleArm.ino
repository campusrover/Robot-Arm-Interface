/* Simple exmaple to control the arm from Charlie's Robot Arm Program. Jacob Smith 11/26/2019*/

//include necessary library
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

// Servo offsets
int shoulder_offset = 0;
int elbow_offset = 0;
int base_offset = 0;

/* pre-calculations */

float hum_sq = HUMERUS * HUMERUS;
float elbow_to_wrist_sq = ELBOW_TO_WRIST * ELBOW_TO_WRIST;


int servoSpeed = 15;

//ServoShield servos; //ServoShield object  assign names to the servo's
VarSpeedServo base_servo, shoulder_servo, elbow_servo, wrist_servo, hand_servo;

/*
 * ******************************************** SETUP  executed once ******************************************************
*/
void setup()

{
  base_servo.attach( BAS_SERVO );    // attaches a servo to an I/O pin   , 544, 2400
  shoulder_servo.attach( SHL_SERVO );
  elbow_servo.attach( ELB_SERVO );
  delay(3000);
}
/*
 * ********************************** LOOP ******************************************************

            set_arm is the key to the arm

 * **********************************************************************************************
*/
void loop()

{
  
  set_arm(0, 0, 60, servoSpeed); // set_arm(  x point in mm,  y point in mm, base_rotation in degrees,  grip_angle in degrees,  Speed )
  delay(4000);

  set_arm( 0, 330, 0 , servoSpeed);
  delay(4000);

}


/* arm positioning routine utilizing inverse kinematics *

  x is distance from base mm, y is height mm, base_rotation  is rotation around base in degrees, gripper_angle is hand rottion in degrees, servospeed is how fast is it to happen 0-300

  void set_arm( uint16_t x, uint16_t y, uint16_t z, uint16_t grip_angle )
  *****************************************************************************************************/
void set_arm( float x, float y, int base_rotation_d, int servoSpeed ) {

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

  /* elbow angle ****************************************************/

  float angle_w = acos(( hum_sq + elbow_to_wrist_sq - s_w ) / ( 2 * HUMERUS * ELBOW_TO_WRIST ));  //This is the required elbow angle, expressed in radians.
  // Spreadsheet I18
  float elb_angle_r = angle_w - shl_angle_r + a1;

  int elb_angle_dm = 0 + degrees( elb_angle_r );      //This is the required elbow angle, expressed in degrees  J18, Q18
 
  //check limits of positioning and go to set zero if it is not and print out error *******
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

  waits = false;
}
