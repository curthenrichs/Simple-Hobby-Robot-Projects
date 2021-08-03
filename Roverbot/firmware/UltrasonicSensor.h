/**
 * UltrasonicSensor
 * @author Curt Henrichs
 * @date 6-24-17
 *
 * UltrasonicSensor abstracts the seeedstudio ultransonic sensor into a discrete
 * software object. Algorithm implemented is drawn from the Ping ultrasonic
 * example software.
 */

#ifndef ULTRASONIC_H
#define ULTRASONIC_H

//==============================================================================
//                               Libraries
//==============================================================================

#include <Arduino.h>

//==============================================================================
//                           Class Declaration
//==============================================================================

/**
 * Sensor object that produces a distance value when requested.
 */
class UltrasonicSensor {

	private:
		byte _triggerPin;			//! pin connected to sensor trigger line
    byte _echoPin;        //! pin conncted to sensor echo line
		long _cachedRead;	    //! last distance reading store

	public:
		/**
		 * Default constructor uses pin parameter to map structure to physical
		 * device.
		 * @param triggerPin is sensor trigger pin on ultrasonic sensor.
     * @param echoPin is sensor echo pin on ultrasonic sensor
		 */
		UltrasonicSensor(byte triggerPin, byte echoPin);
		/**
		 * Sets up interface with hardware, as constructor is called before hardware
		 * in enumerated, thus an error occurs.
		 */
		void begin(void);
		/**
		 * Gets the distance to closest object from the sensor. If distance to
		 * object is a really large value then this is effectively infinity due
		 * to limit on sensor data output.
		 * @return long with a distance in inches
		 */
		long getDistance(void);
		/**
		 * @return gets the last distance read from this sensor.
		 */
		long getCachedDistance(void);
};

#endif
