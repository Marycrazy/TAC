import serial
import time
import datetime
from tqdm import trange

WAIT_TIME = 65 # seconds

# arduino = serial.Serial(port='COM8', baudrate=9600, timeout=.1)
arduino = serial.Serial(port='COM8', baudrate=9600, timeout=.1)

def read():
    data = arduino.readline()
    return data

while True:
    value = read().decode('utf-8').strip()
    data = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S") + " " + value 
    if value != "":
        print(data)
        with open('data.txt', 'a') as f: # saving the value to a file
            f.write(value + '\n')     # saving the value to a file