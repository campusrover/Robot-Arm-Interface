#tells Arduino to move Robot Arm
#import required libraries
import serial
import time
#print initial signal
print "running on PI wait one minute"
#establish serial connection adn wait
ser=serial.Serial("/dev/ttyUSB1",9600)
ser.baudrate=9600
time.sleep(5)
#print moving 
print("moving")
#write only one character
ser.write(b'0')
ser.close()
#print closing message
print("done moving") 