#!/usr/bin/env python

import sys
sys.path.append("/opt/ros/kinetic/lib/python2.7/dist-packages")

import rospy
import time
import serial
from std_msgs.msg import String



# define function is called each time the message is published (by some other node)
def callback(msg):
   print ("I recieved command: " + str(msg.data))
   print ("apple")
   sendCommand(msg.data)


def sendCommand (characterCommand):
	print "a"
	ser.write(characterCommand)
	print "b"
	print ("ARM:"+ser.readline())
	time.sleep(1)
	print "c"

try:
	ser=serial.Serial("/dev/ttyUSB1",9600)
	
	ser.baudrate=9600
	time.sleep(5)

	print("PI:Starting Sequence")
	rospy.init_node('topic_subscriber')
	sub = rospy.Subscriber('armcommand', String, callback)

	# Wait for published topics, exit on ^c
	rospy.spin()
except serial.SerialException as ex:
	print ("USB Not Plugged in")
	time.sleep(5)
except Exception as ex:
	template = "An exception of type {0} occurred. Arguments:\n{1!r}"
	message = template.format(type(ex).__name__, ex.args)
	print message
	time.sleep(5)