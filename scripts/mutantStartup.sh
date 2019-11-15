#run with ssh mutant@mutant.dyn.brandeis.edu 'bash' < '/home/robot/catkin_ws/src/arminterface/scripts/mutantStartup.sh'
#requires gnome terminal and topic subscriber to be installed on pi (as well as ROS)
pkill gnome-terminal-
echo Initializing Setup Variables
export ROS_MASTER_URI=http://mutant.dyn.brandeis.edu:11311/
source /opt/ros/kinetic/setup.bash
source ~/catkin_ws/devel/setup.bash
export DISPLAY=:0.0
sleep 5

echo Starting Roscore and Bringup
#gnome-terminal -e "roscore & roslaunch --wait turtlebot3_bringup turtlebot3_robot.launch"
gnome-terminal -e 'sh -c "roscore & roslaunch --wait turtlebot3_bringup turtlebot3_robot.launch"'
echo Please Unplug and Replug USB on top of robot which has Rubber Band
sleep 30
echo Updating Script on Rasberry Pi
sourceDir=~/catkin_ws/src/Robot-Arm-Interface/
fileName=scripts/topic_subscriber.py
cd $sourceDir
git pull
echo Printing USB Connections
ls /dev/ttyUSB*
echo Starting Local Node
python $sourceDir$fileName
#ssh mutant@mutant.dyn.brandeis.edu 'python' < '/home/robot/catkin_ws/src/arminterface/scripts/topic_subscriber.py'