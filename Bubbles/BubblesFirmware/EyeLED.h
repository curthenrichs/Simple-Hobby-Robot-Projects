/**
 * EyeLED
 * @author Curt Henrichs
 * @date 6-24-17
 *
 * EyeLED implements the RGB led in bubbles head. Uses the Color_t structure to
 * change colors. Several common colors are defined for use with firmware
 * programming.
 */

#ifndef EYE_LED_H
#define EYE_LED_H

//==============================================================================
//                               Libraries
//==============================================================================

#include <Arduino.h>
#include <avr/pgmspace.h>

//==============================================================================
//                       Data Structure Declaration
//==============================================================================

/**
 * Color object for PWM output to an RGB device
 */
typedef struct ColorType {
	byte r;
	byte g;
	byte b;
} Color_t;

//==============================================================================
//                      Constant and Macro Definitions
//==============================================================================

// Common Colors
const Color_t RED = {.r = 255, .g = 0, .b = 0};
const Color_t GREEN = {.r = 0, .g = 255, .b = 0};
const Color_t BLUE = {.r = 0, .g = 0, .b = 255};
const Color_t WHITE = {.r = 255, .g = 255, .b = 255};
const Color_t BLACK = {.r = 0, .g = 0, .b = 0};

// Brightness Range
#define MIN_BRIGHTNESS 0.0
#define MAX_BRIGHTNESS 1.5

//==============================================================================
//                            Class Declaration
//==============================================================================

/**
 * EyeLED defines the RGB leds in Bubbles head that will be controlled through
 * PWM. A global brightness adjustment is also available for broad control of
 * LED light levels (such as a dark enviroment needing a higher brightness).
 */
class EyeLED {
	private:
		// Previous color displayed on LEDs
		Color_t _prevColor;
		// brightness control parameter multiples onto each channel at output.
		// (this does not change the stored previous color)
		float _brightness;
		// physical pinout of device for each LED channel
		byte _rPin, _gPin, _bPin;

	public:
		/**
		 * Constructor for EyeLED uses the provided physical pins to map this object
		 * to the physicla  world. Sets the LEDs to off and brightness to 1 for pass
		 * through behavior.
		 * @param rPin red channel physical PWM pin
		 * @param gPin green channel physical PWM pin
		 * @param bPin blue channel physical PWM pin
		 */
		EyeLED(byte rPin, byte gPin, byte bPin);
		/**
		 * Sets the color on the LEDs. Stores the color set. Adjusts the physical
		 * color by the brightness parameter. (Note: function may saturate if
		 * brightness set higher than 1)
		 * @param color is a color object with rgb values specified.
		 */
		void setColor(Color_t color);
		/**
		 * Gets the previous set color. Does not take into account brightness.
		 * @return color previously set
		 */
		Color_t getColor(void);
		/**
		 * Sets the brightness parameter with the supplied parameter. Value must be
		 * between the minimum and maximum values supported. (Note: LEDs may
		 * saturate if brightness set greater than 1)
		 * @param val is brightness adjustment parameter
		 */
		void setBrightnes(float val);
		/**
		 * Gets the brightness parameter
		 * @return floating point brightness scaler
		 */
		float getBrightness(void);
};

#endif
