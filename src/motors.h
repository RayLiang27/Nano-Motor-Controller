#ifndef MOTORS_H
#define MOTORS_H

#define RIGHT_MOTOR_BACKWARD  4
#define RIGHT_MOTOR_FORWARD   5
#define RIGHT_MOTOR_ENABLE    6
#define LEFT_MOTOR_BACKWARD   7
#define LEFT_MOTOR_FORWARD    8
#define LEFT_MOTOR_ENABLE     9

#define LEFT_WHEEL 0
#define RIGHT_WHEEL 1

void initMotorController();
void setMotorSpeed(uint8_t wheel, int spd);
void setMotorSpeeds(int leftSpeed, int rightSpeed);

#endif