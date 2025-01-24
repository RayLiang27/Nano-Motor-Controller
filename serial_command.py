import serial
import time

# 'COMX' on Windows, '/dev/ttyUSB0' on Linux
port = 'COM5'
baudrate = 9600  # Set baudrate to communciate with device

# Create a serial connection
board = serial.Serial(port, baudrate, timeout=1)

# Wait for the serial connection to initialize
time.sleep(2)

# Function to send data
def send_data(data):
    term_dat = data.encode() + b'\x0D' # Terminate with a CR (ASCII 13) character
    if board.is_open:
        print(term_dat)
        board.write(term_dat)  # Encode the string to bytes and send
    else:
        print("Serial port is not open")

print("Start")

# Wait for any output
while board.in_waiting == 0:
    pass

ready_out = board.readline().decode('utf-8').strip()
print(ready_out)


print(" == SERIAL BEGIN == ")
print("Enter command below (Type \"!exit\" without quotes to exit):")
command = input()

# Receive commands from user
while command.lower() != "!exit":
    print("------------")
    send_data(command)
    while board.in_waiting == 0:
        pass
    ready_out = board.readline().decode('utf-8').strip()
    print(ready_out)
    print("------------")
    print("Enter command below (Type \"!exit\" without quotes to exit):")
    command = input()


board.close()

# try:
#     # Example usage: send data in a loop
#     while True:
#         data = "Hello, world!"  # Replace with your data
#         send_data(data)
#         time.sleep(1)  # Send data every second

# except KeyboardInterrupt:
#     print("Interrupted by user")

# finally:
#     # Close the serial connection
#     board.close()
#     print("Serial connection closed")