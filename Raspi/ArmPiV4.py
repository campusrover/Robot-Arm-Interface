#tells Arduino to move Robot Arm, with specific commands to open and close
#For version 4, the commands move the elbow, shoulder, base, and finger
#prints out Arduino output
import serial
import time

def sendCommand (characterCommand):
	ser.write(characterCommand)
	print "ARM:"+ser.readline()
	time.sleep(1)

ser=serial.Serial("/dev/ttyUSB1",9600)
ser.baudrate=9600
time.sleep(5)

print("PI:Starting Sequence")
#move elbow, shoulder, base, and finger elbow shoulderr out of commission
#sendCommand(b'e')
#sendCommand(b's')
sendCommand(b'b')
sendCommand(b'f')
ser.close()
print("PI:Done with Sequence") 


