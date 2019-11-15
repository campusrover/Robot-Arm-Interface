#run with ssh mutant@mutant.dyn.brandeis.edu 'bash' < '/home/robot/catkin_ws/src/arminterface/scripts/mutantStartup.sh'
export ROS_MASTER_URI=http://mutant.dyn.brandeis.edu:11311/
source /opt/ros/kinetic/setup.bash
source ~/catkin_ws/devel/setup.bash
roscore & roslaunch --wait turtlebot3_bringup turtlebot3_robot.launch 
#make sure local program is updated
sourceDir=~/catkin_ws/src/Robot-Arm-Interface/
fileName=scripts/topic_subscriber.py
cd sourceDir
git pull
python $sourceDir$fileName
#ssh mutant@mutant.dyn.brandeis.edu 'python' < '/home/robot/catkin_ws/src/arminterface/scripts/topic_subscriber.py'