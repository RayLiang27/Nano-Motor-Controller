#include "encoders.h"

// CREDIT TO Daniel Carrasco's article on interrupts in arduino
//    https://www.electrosoftcloud.com/en/pcint-interrupts-on-arduino/

// Encoder values
volatile long right_enc_val;
volatile long left_enc_val;

// Encoder increment table
//    previous ab
//    current AB
// 
const int8_t ENC_INCREMENT [] = {
/*AB  00  01  10  11  */// ab
      0,  1, -1,  0,    // 00
     -1,  0,  0,  1,    // 01
      1,  0,  0, -1,    // 10
      0, -1,  1,  0     // 11
};

void initEncoders()
{
  // set encoder pins as INPUT and PULLUP
  pinMode(LEFT_ENC_PIN_A, INPUT_PULLUP);
  pinMode(LEFT_ENC_PIN_B, INPUT_PULLUP);
  pinMode(RIGHT_ENC_PIN_A, INPUT_PULLUP);
  pinMode(RIGHT_ENC_PIN_B, INPUT_PULLUP);

  // setup interrupt pins
  // LEFT: PORT C
  // RIGHT: PORT D

  // enable interrupts on port C and D
  PCICR |= 0b00000110; 
  // set the encoder pins to be interrupts
  PCMSK1 |= (1 << LEFT_ENC_PIN_A) | (1 << LEFT_ENC_PIN_B);
  PCMSK2 |= (1 << RIGHT_ENC_PIN_A) | (1 << RIGHT_ENC_PIN_B);
}

// ISRs

// Left interrupt
ISR (PCINT1_vect){
  static uint8_t enc_last_l=0;
  
  enc_last_l <<=2; // shift previous reading into ab00
  enc_last_l |= (PINC & 0b00001100) >> 2; // read the current state as abAB
  enc_last_l &= 0xf; // axe off all other previous bits, only abAB left

  left_enc_pos += ENC_INCREMENT[enc_last_l];
}

// Right interrupt
ISR (PCINT2_vect){
  static uint8_t enc_last_r=0;
  
  enc_last_r <<=2; // shift previous reading into ab00
  enc_last_r |= (PIND &  & 0b00001100) >> 2; // read the current state as abAB
  enc_last_r &= 0xf; // axe off all other previous bits, only abAB left

  right_enc_pos += ENC_INCREMENT[enc_last_r];
}

// read the encoder value
long readEncoder(uint8_t enc)
{
  if  (enc == LEFT_ENC)  { return left_enc_val;  }
  else                   { return right_enc_val; }
}

// reset single encoder, both if the entered encoder value is invalid (failsafe)
void resetEncoder(uint8_t enc)
{
  if       (enc == RIGHT_ENC) { right_enc_val = 0L; }
  else if  (enc == LEFT_ENC)  { left_enc_val = 0L;  }
  else     { left_enc_val = 0L; right_enc_val = 0L; }
}

// reset both encoders
void resetEncoders()
{
  resetEncoder(LEFT_ENC);
  resetEncoder(RIGHT_ENC);
}