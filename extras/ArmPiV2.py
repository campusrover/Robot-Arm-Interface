#tells Arduino to move Robot Arm
import serial
import RPi.GPIO as GPIO
import time

ser=serial.Serial("/dev/ttyUSB0",9600)
ser.baudrate=9600
time.sleep(5)

print("moving")
#write only one character
ser.write(b'0')
ser.close()
print("done moving") 
    
