#include "motors.h"

void initMotorController() {
  // set motor pin modes to output
  pinMode(RIGHT_MOTOR_FORWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_BACKWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_ENABLE, OUTPUT);
  pinMode(LEFT_MOTOR_FORWARD, OUTPUT);
  pinMode(LEFT_MOTOR_BACKWARD, OUTPUT);
  pinMode(LEFT_MOTOR_ENABLE, OUTPUT);

  // write all motors LOW
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
}

void setMotorSpeed(uint8_t wheel, int spd) {
  uint8_t reverse = 0;

  if (spd < 0)
  {
    spd = -spd;
    reverse = 1;
  }
  if (spd > 255)
    spd = 255;
  
  if (wheel == LEFT_WHEEL) { 
    if      (reverse == 0) { digitalWrite(LEFT_MOTOR_FORWARD, HIGH);    digitalWrite(LEFT_MOTOR_BACKWARD, LOW);  }
    else if (reverse == 1) { digitalWrite(LEFT_MOTOR_BACKWARD, HIGH);   digitalWrite(LEFT_MOTOR_FORWARD, LOW);   }
    else                   { digitalWrite(LEFT_MOTOR_BACKWARD, LOW);    digitalWrite(LEFT_MOTOR_FORWARD, LOW);   }

    analogWrite(LEFT_MOTOR_ENABLE, spd);
  }
  else {
    if      (reverse == 0) { digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);   digitalWrite(RIGHT_MOTOR_BACKWARD, LOW); }
    else if (reverse == 1) { digitalWrite(RIGHT_MOTOR_BACKWARD, HIGH);  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);  }
    else                   { digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);   digitalWrite(RIGHT_MOTOR_FORWARD, LOW);  }

    analogWrite(RIGHT_MOTOR_ENABLE, spd);
  }


}

// Elminate this function if space looking short
void setMotorSpeeds(int leftSpd, int rightSpd) {
  setMotorSpeed(LEFT_WHEEL, leftSpd);
  setMotorSpeed(RIGHT_WHEEL, rightSpd);
}