#ifndef ENCODERS_H
#define ENCODERS_H

// PORTC pins
#define LEFT_ENC_PIN_A PC4  //pin A4
#define LEFT_ENC_PIN_B PC5  //pin A5

// PORTD pins
#define RIGHT_ENC_PIN_A PD2  //pin 2
#define RIGHT_ENC_PIN_B PD3  //pin 3

#define LEFT_ENC 0
#define RIGHT_ENC 1

void initEncoders();
long readEncoder(uint8_t enc);
void resetEncoder(uint8_t enc);
void resetEncoders();

#endif