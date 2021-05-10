/*
 * File UltrasonicSensor.cpp
 * Author Curt Henrichs
 * Date 3/7/2015
 * Purpose This is the implementation of the UltrasonicSensor class which controls the firing and distance
 * calculations of the ultrasonic sensor used (Seeedstudio)
 */

#include "Arduino.h"
#include "UltrasonicSensor.h"

/*
 * Constructs the ultrasonic sensor
 */
UltrasonicSensor::UltrasonicSensor(int pin)
{
	//set pin
	sensorPin = pin;
	
	//set pinMode
	pinMode(sensorPin, OUTPUT);
	
	//set default value
	digitalWrite(sensorPin, LOW);
}

/*
 * Destructs the ultrasonic sensor
 */
UltrasonicSensor::~UltrasonicSensor()
{
	/*nothing to destroy*/
}

/*
 * Gets the distance in inches from the sensor to the object. Returns a really large junk value
 * if distance is to large or to small.
 */
long UltrasonicSensor::getDistance()
{
	//these are the variabels for the duration of the high pulse and the distance away an object is
	long duration, inches;
	
	//trigger the ping with a two mircosecond high pulse then drop lw before switching to input
	pinMode(sensorPin, OUTPUT);
	digitalWrite(sensorPin, LOW);
	delayMicroseconds(2);
	digitalWrite(sensorPin, HIGH);
	delayMicroseconds(5);
	digitalWrite(sensorPin, LOW);
	
	//switch to input then wait for the trigger
	pinMode(sensorPin, INPUT);
	duration = pulseIn(sensorPin, HIGH);
	
	//convert to inches
	inches = duration/74/2;
	
	//give system time to reset values
	delay(100);
	
	//return the value to the program
	return inches;
}
