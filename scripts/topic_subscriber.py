#!/usr/bin/env python
import os,sys
sys.stdout = os.fdopen(sys.stdout.fileno(), 'w', 1) # line buffering

sys.path.append("/opt/ros/kinetic/lib/python2.7/dist-packages")

import rospy
import time
import serial
from std_msgs.msg import String

# define function is called each time the message is published (by some other node)
def callback(msg):
  	print ("\tPI:recieved command: " + str(msg.data))
   	sendCommand(msg.data)


def sendCommand (characterCommand):
	ser.write(characterCommand)
	response=ser.readline()
	#if there was no response, update variable to default message
	if not response:
		response="\tElement did not respond in time"
	serialPub.publish(response)
	print(response)
	print("")

# Make this into a ROS node.
rospy.init_node('arminterface')

#subscribe to arm command topic
sub = rospy.Subscriber('armcommand', String, callback)
# Prepare to publish topic `counter`
serialPub = rospy.Publisher('armresponse', String, queue_size=10)

try:
	#intialize serial connection
	ser=serial.Serial("/dev/ttyUSB1",9600,timeout=5)	
	ser.baudrate=9600
	print("Starting Serial Connection")

	print("PI:Starting Sequence")
	#consume Arduino wellcome message
	print(ser.readline())
	print(ser.readline())
	print(ser.readline())
	
	#publih distance
	serialPub.publish("First Publish")
	# wait
	rospy.spin()

except serial.SerialException as ex:
	print ("USB Not Plugged in")
	time.sleep(5)
except Exception as ex:
	template = "An exception of type {0} occurred. Arguments:\n{1!r}"
	message = template.format(type(ex).__name__, ex.args)
	print message
	time.sleep(5)
