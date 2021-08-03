/**
 * UltrasonicSensor
 * @author Curt Henrichs
 * @date 6-24-17
 *
 * UltrasonicSensor abstracts the seeedstudio ultransonic sensor into a discrete
 * software object. Algorithm implemented is drawn from the Ping ultrasonic
 * example software.
 */

 //==============================================================================
 //                               Libraries
 //==============================================================================

#include "UltrasonicSensor.h"

//==============================================================================
//                           Class Implementation
//==============================================================================

/**
 * Default constructor uses pin parameter to map structure to physical
 * device.
 * @param pin is sensor IO pin on ultrasonic sensor.
 */
UltrasonicSensor::UltrasonicSensor(byte triggerPin, byte echoPin){
	_triggerPin = triggerPin;
  _echoPin = echoPin;
	_cachedRead = 0;
}

/**
 * Sets up interface with hardware, as constructor is called before hardware
 * in enumerated, thus an error occurs.
 */
void UltrasonicSensor::begin(void){
  pinMode(_echoPin,INPUT);
  pinMode(_triggerPin, OUTPUT);
}

/**
 * Gets the distance to closest object from the sensor. If distance to
 * object is a really large value then this is effectively infinity due
 * to limit on sensor data output.
 * @return long with a distance in inches
 */
long UltrasonicSensor::getDistance(void){
 digitalWrite(_triggerPin, LOW);
 delayMicroseconds(2);
 digitalWrite(_triggerPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(_triggerPin, LOW);

 long duration = pulseIn(_echoPin, HIGH);
 _cachedRead = duration / 74 / 2;

  Serial.println(_cachedRead);
 
 return _cachedRead;
}

/**
 * @return gets the last distance read from this sensor.
 */
long UltrasonicSensor::getCachedDistance(void) {
	return _cachedRead;
}
