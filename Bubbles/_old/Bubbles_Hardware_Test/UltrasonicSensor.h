/*
 * File UltrasonicSensor.h
 * Author Curt Henrichs
 * Date 3/7/2015
 * Purpose This is the desricption of the UltrasonicSensor class which controls the firing and distance
 * calculations of the ultrasonic sensor used (Seeedstudio)
 */

#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "Arduino.h"

class UltrasonicSensor
{
	private:
		int sensorPin;
	public:
		UltrasonicSensor(int pin);
		~UltrasonicSensor();
		long getDistance();
};

#endif
