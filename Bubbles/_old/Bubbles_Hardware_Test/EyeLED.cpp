/*
 * File EyeLED.cpp
 * Author Curt Henrichs
 * Date 3/7/2015
 * Purpose This is the implmentation of the EyeLED class. The goal is to represent the color of the LEDs in Bubbles eyes
 * and abstracting the hardware details from the client.
 */

//NOTE: This class is not complete and needs to be built with more color options so as of now please do not use

#include "EyeLED.h"

/*
 * Constructor
 */
EyeLED::EyeLED(int r,int g,int b)
{
	//set pins
	redLED = r;
	greenLED = g;
	blueLED = b;
	
	//set pinMode
	pinMode(redLED,OUTPUT);
	pinMode(greenLED,OUTPUT);
	pinMode(blueLED,OUTPUT);
	
	//set default values
	digitalWrite(redLED,LOW);
	digitalWrite(greenLED,LOW);
	digitalWrite(blueLED,LOW);
}

/*
 * Destructor
 */
EyeLED::~EyeLED()
{
	/*nothing to destroy*/
}

/*
 * Gives LEDS red command
 */
void EyeLED::red()
{
	digitalWrite(redLED,HIGH);
	digitalWrite(greenLED,LOW);
	digitalWrite(blueLED,LOW);
}

/*
 * Gives LEDS green command
 */
void EyeLED::green()
{
	digitalWrite(redLED,LOW);
	digitalWrite(greenLED,HIGH);
	digitalWrite(blueLED,LOW);
}

/*
 * Gives LEDS blue command
 */
void EyeLED::blue()
{
	digitalWrite(redLED,LOW);
	digitalWrite(greenLED,LOW);
	digitalWrite(blueLED,HIGH);
}

/*
 * Gves LEDS white command
 */
void EyeLED::white()
{
	digitalWrite(redLED,HIGH);
	digitalWrite(greenLED,HIGH);
	digitalWrite(blueLED,HIGH);
}

/*
 * Turn off all LEDS
 */
void EyeLED::off()
{
	digitalWrite(redLED,LOW);
	digitalWrite(greenLED,LOW);
	digitalWrite(blueLED,LOW);
}
