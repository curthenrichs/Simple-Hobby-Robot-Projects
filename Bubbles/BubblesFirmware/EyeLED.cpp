/**
 * EyeLED
 * @author Curt Henrichs
 * @date 6-24-17
 *
 * EyeLED implements the RGB led in bubbles head. Uses the Color_t structure to
 * change colors. Several common colors are defined for use with firmware
 * programming.
 */

 //==============================================================================
 //                               Libraries
 //==============================================================================

#include "EyeLED.h"

//==============================================================================
//                             Class Implementation
//==============================================================================

/**
 * Constructor for EyeLED uses the provided physical pins to map this object
 * to the physicla  world. Sets the LEDs to off and brightness to 1 for pass
 * through behavior.
 * @param rPin red channel physical PWM pin
 * @param gPin green channel physical PWM pin
 * @param bPin blue channel physical PWM pin
 */
EyeLED::EyeLED(byte rPin, byte gPin, byte bPin){
	//member initialization
	_rPin = rPin;
	_gPin = gPin;
	_bPin = bPin;
	_brightness = 1;
	_prevColor = {0,0,0};

	//configure hardware
	pinMode(_rPin, OUTPUT);
	pinMode(_gPin, OUTPUT);
	pinMode(_bPin, OUTPUT);
	setColor(_prevColor);
}

/**
 * Sets the color on the LEDs. Stores the color set. Adjusts the physical
 * color by the brightness parameter. (Note: function may saturate if
 * brightness set higher than 1)
 * @param color is a color object with rgb values specified.
 */
void EyeLED::setColor(Color_t color){
	_prevColor = color;
	analogWrite(_rPin, _brightness * color.r);
	analogWrite(_gPin, _brightness * color.g);
	analogWrite(_bPin, _brightness * color.b);
}

/**
 * Gets the previous set color. Does not take into account brightness.
 * @return color previously set
 */
Color_t EyeLED::getColor(void){
	return _prevColor;
}

/**
 * Sets the brightness parameter with the supplied parameter. Value must be
 * between the minimum and maximum values supported. (Note: LEDs may
 * saturate if brightness set greater than 1)
 * @param val is brightness adjustment parameter
 */
void EyeLED::setBrightnes(float val){
	if(val >= MIN_BRIGHTNESS && val <= MAX_BRIGHTNESS){
		_brightness = val;
	}
}

/**
 * Gets the brightness parameter
 * @return floating point brightness scaler
 */
float EyeLED::getBrightness(void){
	return _brightness;
}
