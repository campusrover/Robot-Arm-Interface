COSI 119A Final Project Arm Interfacing
===============

Jacob Smith, Fall 2019, Brandeis University

My project is to interface an arm to the mutant campus rover.

See the project Proposal in extras folder

using [VarSpeedServo](https://github.com/netlabtoolkit/VarSpeedServo) Library as background code, all my work is in examples and extras folder

Functionality so far

### Oct 25-31:

#### Getting Arm to Move

(provided)  Sweep Controls Servo on Port 7

(provided) *RobotArmScript* Arduino Program to control rest of the Arm

#### Getting Arduino to talk to Rasberry Pi

*(provided)  ArmArduinoV1*, lets the Arduino talk to the Pi

*(provided)  PiArduinoV1* lets teh Pi talk to the Arduino

​					Screenshot showing Message from Arduino being printed on Rasberry Pi

![V1 Where Arduino can talk to Pi](docs/V1.png)

#### **Getting Rasberry Pi to Talk to Arduino**

(provided)  ArmArduinoV2*, lets the Arduino talk to the Pi

*(provided)  PiArduinoV2* lets the Pi talk to the Arduino

​	It sends a serial command to the Arduino, which reads it and moves the servo

​	![PiAQrduinoV2 Script](docs/V2Script.png)

#### **Workflow improvements**			

​		Now that the basic premise was set up, I remounted the Servo Arm onto a robot chassis. Also, I can log into the mutant robot and execute python scripts over ssh. 

​				`ls /dev/tty*`		Lists available USb ports, look for USB 0

​				`ssh mutant@mutant.dyn.brandeis.edu 'python' < '/home/robot/catkin_ws/src/arminterface/Raspi/ArmPiV4.py'`      Executes a python file on ssh without copying that file to the mutant rasberry Pi, 40 second time lag

​		These workflow improvements should allow me to test the arm much more quickly than plugging in to the mutant and and plugging in the arm etc.

​			![Condensed Arm](docs/ArmCondensed.jpg)

​		Also, I am running the commands on the mutant robot, where the arm now has a port.

#### **Two Way Communication**

​		*ArmArduinoV3*, Opens the gripper if receives o character over serial, closes if c character

​		*PiArduinoV3* Sends the open and close characters, also two way communication

​		This is the simplest expression of the interface required for the final project.

​			First, we check that the arm shows up in hte list of USB ports as USB 0

​					![USB Ports Demonstration](docs/USBV3.gif)

​		Then, we run the ArmPiV3 script over ssh, which moves the arm and displays output

​					![Output of V3](docs/OutputV3.gif)

​			Finally, the servo opens and closes!

![Servo MovingV3](docs/ServoMovingV3.gif)

​					Here is a video of this stage:

​						 [![Shows Python file controlling gripper on  arm](http://img.youtube.com/vi/m0WW0uCtgWg/0.jpg)](http://www.youtube.com/watch?v=m0WW0uCtgWg "Two Way Arm Interfacing Video")



#### Future Work

​			The main future goal is to interface the arm to ROS. In the short term, I want to decrease the lag, enable the arm to respond to keyboard input, and get the arm fixed

### Nov 1-7:

This week, I focused on the hardware of the arm, taking it apart, putting it back together, and mounting it to the Mutant Robot. Version 4 of the Arduino and Pi scripts show updated functionality, where the whole arm can be controlled.

​	First, I replaced the broken motors on the arm, this shows the base motor rotating after I lined it up again 	absolute position matters for servos):

![The Gears of the base of the arm](docs/BaseMechanics.gif)

​	Then, I mounted the arm on the mutant, note how there is enough clearance for the lidar because of the 	washers I added:

![New Waffle level showing clearance for arm](/home/robot/catkin_ws/src/arminterface/docs/LidarMount.gif)

​	Version 4 of my scripts allow mulktiple parts of the arm to be controlled, shown here is the console output and robot motion.

![The Console inder Version 4](docs/V4Console.png)

![Arm Mounted on Robot](docs/ArmMount.gif)

A video of this week's work can be found [here](https://www.youtube.com/watch?v=U1VSVlQWPBY) 

**Future Work:**

By Next week, I will have communicated with Charlie about the battery and broken motors, and plugged the arm into a publisher/subscriber model in ROS. The deliverable will be a video of me moving the arm as I did this week but with ROS scripts.

### Nov 8-15

​	Current projects: Charlie is remounting the arm

​	I'm looking into writing auto boot up ssh script for pi, and gazebo simulation

Links http://gazebosim.org/tutorials/?tut=ros_urdf http://wiki.ros.org/joint_trajectory_controller Pito doesn;t like https://answers.ros.org/question/38694/running-ros-across-multiple-machines/

Trying to get positon from servos, Charly convinced me there is no way to get position because there is no position wire.

http://forums.trossenrobotics.com/tutorials/how-to-diy-128/get-position-feedback-from-a-standard-hobby-servo-3279/

Arm is Moving function eixst in varspeedservo

http://forums.trossenrobotics.com/tutorials/how-to-diy-128/get-position-feedback-from-a-standard-hobby-servo-3279/

**Sources**			

[1] Links fix Arduino download error https://www.arduino.cc/en/Guide/Linux

[2] Get Arduino to listen to Serial https://www.instructables.com/id/Connect-Your-Raspberry-Pi-and-Arduino-Uno/

[3]Get Pi to talk to Serial https://pyserial.readthedocs.io/en/latest/shortintro.html

[4] Run a Python File remotely https://www.shellhacks.com/ssh-execute-remote-command-script-linux/

