#!/usr/bin/env python
#Publishes Commands to ROS ARM in format below

import rospy
from std_msgs.msg import String

# Make this into a ROS node.
rospy.init_node('topic_publisher')

# Prepare to publish topic `counter`
pub = rospy.Publisher('armcommand', String, queue_size=10)

# sleep at rate of loops per second
rate = rospy.Rate(.25)
commands= ["MANIP 1 \n","ARM 0 330 0 20 \n","MANIP 0 \n","MANIP 2 \n","ARM 0 0 60 20 \n"]
index=0
# loop until ^c
while not rospy.is_shutdown():
    #iterates through list of commands
    command=commands[index]
    if index==len(commands)-1:
       index=0 
    else:
        index=index+1
        

    print "Arm will do: " +command
    pub.publish(command) 
    rate.sleep()