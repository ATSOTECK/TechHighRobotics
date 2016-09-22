#ifndef _PORTS
#define _PORTS

//joysticks
#define L_JOYSTICK_DRIVE	1
#define R_JOYSTICK_DRIVE	2
#define JOYSTICK_ARM		3
#define JOYSTICK_HAND		4

//PWM
#define DRIVE_LEFT_MOTOR	3
#define DRIVE_RIGHT_MOTOR	4
#define ARM_MOTOR			7
#define MINIBOT_SERVO_1		10
#define MINIBOT_SERVO_2		9

//analogue input
#define GYRO_PORT	1

//digital io
#define ARM_ISDOWN		1
#define ARM_ENC_A		2
#define ARM_ENC_B		3
#define ARM_ISUP		4
#define DRIVE_ENC_A		9
#define DRIVE_ENC_B		10
#define LINE_SENSOR 	11 //through 14

//relay
#define HAND_TOP_MOTOR		7
#define HAND_BOTTOM_MOTOR	8

//solenoids
#define TRANSMISSION_1HIGH	1
#define TRANSMISSION_1LOW	2
#define TRANSMISSION_2HIGH	3
#define TRANSMISSION_2LOW	4
#define MINIBOT_DEPLOY_ON	5
#define MINIBOT_DEPLOY_OFF	6

//driverstation io
#define ROTARY_SWITCH		1 //through 8
#define MINIBOT_SHOOT		9
#define MINIBOT_DEPLOY		10

#endif
