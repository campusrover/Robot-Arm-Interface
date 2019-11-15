#!/usr/bin/env python

import sys
sys.path.append("/opt/ros/kinetic/lib/python2.7/dist-packages")

import rospy
import time
import serial
from std_msgs.msg import String

print("mark")

# define function is called each time the message is published (by some other node)
def callback(msg):
  	print ("\tPI:recieved command: " + str(msg.data))
   	sendCommand(msg.data)


def sendCommand (characterCommand):
	ser.write(characterCommand)
	response=ser.readline()
	if response:
		print ("\tARM:"+ response)
	else:
		print ("\tElement did not respond in time")
	print("")
try:
	ser=serial.Serial("/dev/ttyUSB1",9600,timeout=5)	
	ser.baudrate=9600
	print("Starting Serial Connection")

	print("PI:Starting Sequence")
	#consume Arduino wellcome message
	print(ser.readline())
	print(ser.readline())

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
