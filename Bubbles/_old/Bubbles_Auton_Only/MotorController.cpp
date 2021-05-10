/*
 * File MotorController.cpp
 * Author Curt Henrichs
 * Date 3/7/2015
 * Purpose This is the implmentation of the MotorController class which controls the action of the custom
 * motor control circuit on Bubbles.
 */

#include "Arduino.h"
#include "MotorController.h"

/*
 *
 */
MotorController::MotorController(int dir,int stp)
{
	//set pins
	directionPin = dir;
	stopPin = stp;
	
	//set pinMode
	pinMode(directionPin,OUTPUT);
	pinMode(stopPin,OUTPUT);
	
	//set default Values
	digitalWrite(directionPin,HIGH);
	digitalWrite(stopPin,LOW);
}

/*
 * Destructor
 */
MotorController::~MotorController()
{
	/*Nothing to dstruct*/
}

/*
 * Stops the motor
 */
void MotorController::stop()
{
	digitalWrite(stopPin,HIGH);
}

/*
 * Sends the motor in the forward direction
 */
void MotorController::forward()
{
	digitalWrite(directionPin,LOW);
	digitalWrite(stopPin,LOW);
}

/*
 * Sends the motor in the reverse direction
 */
void MotorController::reverse()
{
	digitalWrite(directionPin,HIGH);
	digitalWrite(stopPin,LOW);
}
