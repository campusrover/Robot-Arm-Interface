#!/usr/bin/env python
# Don't forget to chmod +x topic_publisher.py

import rospy
from std_msgs.msg import String

# Make this into a ROS node.
rospy.init_node('topic_publisher')

# Prepare to publish topic `counter`
pub = rospy.Publisher('armcommand', String, queue_size=10)

# sleep at .1 loops per second
rate = rospy.Rate(.1)
#command=String()
#command.data='f'
command='apple'
# loop until ^c
while not rospy.is_shutdown():
    pub.publish(command)
    rate.sleep()