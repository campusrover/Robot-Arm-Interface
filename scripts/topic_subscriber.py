#!/usr/bin/env python

import rospy
import serial
from std_msgs.msg import String

# define function is called each time the message is published (by some other node)
def callback(msg):
   print "I recieved command\t" + str(msg.data)
   sendCommand(msg.data)


def sendCommand (characterCommand):
	ser.write(characterCommand)
	print "ARM:"+ser.readline()
	time.sleep(1)

ser=serial.Serial("/dev/ttyUSB1",9600)
ser.baudrate=9600
time.sleep(5)

print("PI:Starting Sequence")
rospy.init_node('topic_subscriber')
sub = rospy.Subscriber('armcommand', String, callback)

# Wait for published topics, exit on ^c
rospy.spin()
