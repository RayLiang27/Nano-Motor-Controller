// Define the necessary commands

// Reserve 0000 0000 to 0001 1111 for special signifying characters


#ifndef COMMANDS_H
#define COMMANDS_H

// 
#define ARG_DELIMITER ' '
#define CMD_TERMINATE 13
#define BAUDRATE 9600
#define ARG_MAX_SIZE 8

// Analog Pin commands
#define ANALOG_READ 'a'
#define ANALOG_WRITE 'w'

// Digital Pin commands
#define DIGITAL_READ 'd'
#define DIGITAL_WRITE 'x'

// Encoder commands
#define READ_ENCODERS 'e'
#define ZERO_ENCODERS 'z'

// Motor setting commands
#define SET_MOTOR_SPEEDS 'm'
#define SET_MOTOR_RPM 'r'

// ...anything else?

#endif