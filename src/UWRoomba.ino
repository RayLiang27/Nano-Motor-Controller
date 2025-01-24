#include "Arduino.h"
#include "commands.h"
#include "motors.h"
#include "encoders.h"

// command 
char cmd = '\0';

// arguments
int arg[4];
uint8_t argIndex = 0;

// individual argument as string
char argStr[ARG_MAX_SIZE];
uint8_t strIndex = 0;

// Decision for command running
void runCmd()
{
  switch (cmd)
  {
    case ANALOG_READ:
      Serial.println(analogRead(arg[0]));
      break;

    case ANALOG_WRITE:
      analogWrite(arg[0], arg[1]);
      Serial.println("OK"); 
      break;

    case DIGITAL_READ:
      Serial.println(digitalRead(arg[0]));
      break;
    
    case DIGITAL_WRITE:
      if (arg[1] == 0) digitalWrite(arg[0], LOW);
      else if (arg[1] == 1) digitalWrite(arg[0], HIGH);
      Serial.println("OK");
      break;

    // TODO: Uncomment code and test encoders
    case READ_ENCODERS:
      // Serial.print(readEncoder(LEFT));
      // Serial.print(" ");
      // Serial.println(readEncoder(RIGHT));
      break;

    case ZERO_ENCODERS:
      // resetEncoders();
      // resetPID();
      // Serial.println("OK");
      break;

    case SET_MOTOR_SPEEDS:
      // this one requires the PID feedback loop
      setMotorSpeeds(0, 0);
      break;

    case SET_MOTOR_RPM:
      setMotorSpeeds(arg[0], arg[1]);
      Serial.println("OK");
      break;

    default:
      Serial.println("INVALID");
      break;
  }

  // TEST SERIAL READ/WRITE OVER USB

  //char returnStr[12] = "RECEIVED: x\0";
  // if (cmd == ANALOG_READ || cmd == ANALOG_WRITE || cmd == DIGITAL_READ || cmd == DIGITAL_WRITE ||
  //     cmd == READ_ENCODERS || cmd == ZERO_ENCODERS || cmd == SET_MOTOR_SPEEDS || cmd == SET_MOTOR_RPM)
  // {
  //   Serial.print("VALID: ");
  //   for (uint8_t i = 0; i < argIndex; i++)
  //   {
  //     Serial.print(arg[i]);
  //     Serial.print(", ");
  //   }
  //   Serial.println("ARGS");
  // }
  // else
  // {
  //   Serial.println("INVALID");
  // }
}

// Reset all commands and arguments
void clrCmd()
{
  cmd = '\0';

  memset(arg, 0, sizeof(arg));
  argIndex = 0;

  memset(argStr, 0, sizeof(argStr));
  strIndex = 0;
}

void setup()
{
  Serial.begin(9600);
  initMotorController();
  // TODO: uncomment when testing encoders
  // initEncoders();
  delay(1000);
  Serial.println("Ready");
}

void loop()
{
  // Read bytes if there are any
  while (Serial.available() > 0)
  {
    // read one byte at a time
    char chr = Serial.read();

    // The full command terminates at CR (ascii code 13)
    if (chr == CMD_TERMINATE)
    {
      // terminate char array
      argStr[strIndex] = '\0';
      if (strIndex > 0)
      {
        // parse as integer and add to argument array
        arg[argIndex++] = atoi(argStr);
      }

      // run the command
      runCmd();
      // clear everything
      clrCmd();
    }
    // Delimit arguments
    else if (chr == ARG_DELIMITER)
    {
      // terminate char array
      argStr[strIndex] = '\0';
      if (strIndex > 0)
      {
        // parse as integer and add to argument array
        arg[argIndex++] = atoi(argStr);
      }

      // clear argument string and strIndex
      memset(argStr, 0, sizeof(argStr));
      strIndex = 0;
    }
    // general commands
    else
    {
      if (cmd == '\0')
      {
        cmd = chr;
      }
      else
      {
        // push only the first 8 args
        if (strIndex < ARG_MAX_SIZE - 1)
          argStr[strIndex++] = chr;
      }
    }
  }

  // don't blow up
  delay(5);
}