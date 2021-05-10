 /**
  * MotorController
	* @author Curt Henrichs
	* @date 6-24-17
	*
	* Implements the motor controller object that is used to route the motor
	* signals from Bubbles hardware to motor, select direction, and prevent
	* Bubbles from moving at all.
	*/

#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

//==============================================================================
//                                Libraries
//==============================================================================

#include <Arduino.h>

//==============================================================================
//                             Class Declaration
//==============================================================================

/**
 * MotorController handles the interface between the hardware motor, Bubbles
 * internal control signals, and the aims of the firmware interface.
 */
class MotorController{
	private:
		// Direction control pin (clockwise, counter-clockwise)
		byte _dirPin;
		// Stop pin, disables the active control of the motor.
		byte _stopPin;

	public:
		/**
		 * Constructor for motor controller maps the pins addresses to the software
		 * structure.
		 * @param dirPin direction control pin
		 * @param stopPin enable/disable pin for controller
		 */
		MotorController(byte dirPin, byte stopPin);
		/**
		 * Enable the motor controller
		 * @param enable status flag to control state of controller
		 */
		void enable(bool enable);
		/**
		 * Commands the motor in the forward direction (what ever that means)
		 */
		void forward(void);
		/**
		 * Commands the motor in the reverse direction (what ever that means)
		 */
		void reverse(void);
};

#endif
