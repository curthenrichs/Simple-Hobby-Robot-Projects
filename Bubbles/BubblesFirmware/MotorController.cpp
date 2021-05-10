/**
 * MotorController
 * @author Curt Henrichs
 * @date 6-24-17
 *
 * Implements the motor controller object that is used to route the motor
 * signals from Bubbles hardware to motor, select direction, and prevent
 * Bubbles from moving at all.
 */

//==============================================================================
//                                Libraries
//==============================================================================

#include "MotorController.h"

//==============================================================================
//                           Class Implementation
//==============================================================================

/**
 * Constructor for motor controller maps the pins addresses to the software
 * structure.
 * @param dirPin direction control pin
 * @param stopPin enable/disable pin for controller
 */
MotorController::MotorController(byte dirPin, byte stopPin){
	//initializes members
	_dirPin = dirPin;
	_stopPin = stopPin;

	//configure hardware
	pinMode(_dirPin,OUTPUT);
	pinMode(_stopPin,OUTPUT);
	digitalWrite(_dirPin,LOW);
	digitalWrite(_stopPin,LOW);
}

/**
 * Enable the motor controller
 * @param enable status flag to control state of controller
 */
void MotorController::enable(bool enable){
	digitalWrite(_stopPin,!enable);
  Serial.print(F("In motorcontroller enable: "));
  Serial.println(enable);
}

/**
 * Commands the motor in the forward direction (what ever that means)
 */
void MotorController::forward(void){
	digitalWrite(_dirPin,LOW);
  Serial.println(F("In motorcontroller forward"));
}

/**
 * Commands the motor in the reverse direction (what ever that means)
 */
void MotorController::reverse(void){
	digitalWrite(_dirPin,HIGH);
  Serial.println(F("In motorcontroller backward"));
}
