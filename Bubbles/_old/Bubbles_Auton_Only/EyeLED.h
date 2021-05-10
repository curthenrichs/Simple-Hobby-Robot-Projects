/*
 * File EyeLED.h
 * Author Curt Henrichs
 * Date 3/7/2015
 * Purpose This is the definition of the EyeLED class. The goal is to represent the color of the LEDs in Bubbles eyes
 * and abstracting the hardware details from the client.
 */

#ifndef EYE_LED
#define EYE_LED

#include "Arduino.h"

class EyeLED
{
	private:
		int redLED;
		int greenLED;
		int blueLED;
	public:
		EyeLED(int r, int g, int b);
		~EyeLED();
		void red();
		void blue();
		void green();
		void white();
		void off();
};

#endif
