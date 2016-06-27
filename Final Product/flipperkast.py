import termios, sys, os
import pygame
import serial
import time

time.sleep(2) # delay for 2 seconds
TERMIOS = termios
ser = serial.Serial('/dev/ttyACM0', 9600)
s = [0,1]
pygame.mixer.init()

while 1:
    read_serial=ser.readline()
    s[0] = str(int (ser.readline(), 16))
    execfile("/home/pi/Flipperkast/music.py")
        
while not done:
    for event in pygame.event.get():
        if event.type == KEYDOWN:
            done = True
