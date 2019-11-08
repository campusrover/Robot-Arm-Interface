#!/usr/bin/env python

import rospy
from std_msgs.msg import String

# define function is called each time the message is published (by some other node)
def callback(msg):
   #print "I recieved command" + str(msg.data)

rospy.init_node('topic_subscriber')
sub = rospy.Subscriber('armcommand', String, callback)

# Wait for published topics, exit on ^c
rospy.spin()
