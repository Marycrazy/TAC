import serial
arduino = serial.Serial(port='COM4', baudrate=9600, timeout=.1)
def read():
data = arduino.readline()
return data
while True:
value = read().decode('utf-8').strip()
print(value) # printing the value