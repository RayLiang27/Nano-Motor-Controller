// #include "Arduino.h"
// #include "commands.h"
// #include "config.h"
// #include "string.h"

// // TODO: Rescope things

// // command 
// char cmd = '\0';

// // arguments
// int arg[8];
// uint8_t argIndex = 0;

// // individual argument as string
// char argStr[16];
// uint8_t index = 0;

// void runCmd()
// {

//   switch (cmd)
//   {
//     case ANALOG_READ:
//       Serial.println(analogRead(arg1));
//       break;

//     case ANALOG_WRITE:
//       analogWrite(arg1, arg2);
//       Serial.println("OK"); 
//       break;

//     case DIGITAL_READ:
//       Serial.println(digitalRead(arg1));
//       break;
    
//     case DIGITAL_WRITE:
//       if (arg2 == 0) digitalWrite(arg1, LOW);
//       else if (arg2 == 1) digitalWrite(arg1, HIGH);
//       Serial.println("OK");
//       break;

//     case READ_ENCODERS:
//       // Serial.print(readEncoder(LEFT));
//       // Serial.print(" ");
//       // Serial.println(readEncoder(RIGHT));
//       break;

//     case ZERO_ENCODERS:
//       // resetEncoders();
//       // resetPID();
//       // Serial.println("OK");
//       break;

//     case SET_MOTOR_SPEEDS:
//       setMotorSpeeds(0, 0);
//       break;

//     case SET_MOTOR_RPM:
//       break;

//     default:
//       Serial.println("Invalid command");
//       break;
//   }
// }

// // Reset all commands and arguments
// void clrCmd()
// {
//   cmd = '\0';

//   memset(arg, 0, sizeof(arg));
//   argIndex = 0;

//   memset(argStr, 0, sizeof(argStr));
//   index = 0;
// }

// void setup()
// {
//   Serial.begin(BAUDRATE);
//   clrCmd();
// }

// void loop()
// {
//   // Read bytes if there are any
//   while (Serial.available() > 0)
//   {
//     // read one byte at a time
//     char chr = Serial.read();

//     // The full command terminates at CR (ascii code 13)
//     if (chr == 13)
//     {
//       // terminate char array
//       argStr[index] = '\0';

//       // run the command
//       runCmd();
//       // clear everything
//       clrCmd();
//     }
//     // Delimit arguments
//     else if (chr == ARG_DELIMITER)
//     {
//       // terminate char array
//       argStr[index] = '\0';

//       // parse as integer and add to argument array
//       arg[argIndex++] = atoi(argStr);

//       // clear argument string and index
//       memset(argStr, 0, sizeof(argStr));
//       index = 0;
//     }
//     // general commands
//     else
//     {
//       if (cmd == '\0')
//       {
//         cmd = chr;
//       }
//       else
//       {
//         // truncate anything larger than 16 characters
//         if (index > 15)
//           continue;
//         argStr[index++] = chr;
//       }
//     }
//   }

//   // PID control loop (eventually)
// }