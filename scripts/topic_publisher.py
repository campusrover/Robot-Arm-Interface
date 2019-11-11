#!/usr/bin/env python
# Don't forget to chmod +x topic_publisher.py

import rospy
import random
from std_msgs.msg import String

# Make this into a ROS node.
rospy.init_node('topic_publisher')

# Prepare to publish topic `counter`
pub = rospy.Publisher('armcommand', String, queue_size=10)

# sleep at rate of loops per second
rate = rospy.Rate(.1)
#command=String()
#command.data='f'
command='f'


# loop until ^c
while not rospy.is_shutdown():
    #make command random
    command=random.choice("sfb")
    if len(command)!=1:
        print "The Message is too big"
    else:
        print "Arm will do: " +command
        pub.publish(command) 
    rate.sleep()