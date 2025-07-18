import serial
import time

ser = serial.Serial('/dev/ttyS0', 9600)
time.sleep(2)

ser.write(b'Hello, Teensy!')

ser.close()
