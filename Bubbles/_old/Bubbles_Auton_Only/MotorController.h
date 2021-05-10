/*
 * File MotorController.h
 * Author Curt Henrichs
 * Date 3/7/2015
 * Purpose This is the description of the MotorController class which controls the action of the custom
 * motor control circuit on Bubbles.
 */

#ifndef MOTOR_CONTROL
#define MOTOR_CONTROL

#include "Arduino.h"

class MotorController
{
	private:
		int directionPin;
		int stopPin;
	public:
		MotorController(int dir,int stp);
		~MotorController();
		void stop();
		void forward();
		void reverse();
};

#endif
