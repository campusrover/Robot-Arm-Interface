import serial
import RPi.GPIO as GPIO
import time

ser=serial.Serial("/dev/ttyUSB0",9600)
ser.baudrate=9600

while True:
    read_ser=ser.readline()
    print(read_ser)
    