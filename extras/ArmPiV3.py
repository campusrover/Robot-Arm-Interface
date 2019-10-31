#tells Arduino to move Robot Arm, with specific commands to open and close
#prints out Arduino output

import serial
import time

ser=serial.Serial("/dev/ttyUSB1",9600)
ser.baudrate=9600
time.sleep(5)

print("PI:Starting Sequence")
#Tell finger to open
ser.write(b'0')
print "ARM:"+ser.readline()
time.sleep(1)

#Tell finger to close
ser.write(b'c')
print "ARM:"+ser.readline()
time.sleep(1)

#Show error code
ser.write(b'a')
print "ARM:"+ser.readline()


ser.close()
print("PI:Done with Sequence") 
    
