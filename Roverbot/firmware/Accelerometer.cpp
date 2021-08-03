/**
 * Accelerometer
 * @author Curt Henrichs
 * @date 7-7-21
 * 
 * Thin wrapper around Adafruit accelerometer library. Used to extract
 * the relevant data for roverbot.
 */

//==============================================================================
//                                  Libraries
//==============================================================================

#include "Accelerometer.h"

#include "HardwareConfig.h"
#include <Wire.h>

//==============================================================================
//                            Class Implementation
//==============================================================================

/**
 * Constructor creates a new sensor
 */
Accelerometer::Accelerometer(void) : sensor() {
  x =  y = z = 0;
}

/**
     * Starts I2C comms
     */
void Accelerometer::begin(void) {
  sensor.begin(I2C_ACCEROMETER_ADDRESS);
}

/**
 * Queries the I2C device for latest state
 */
void Accelerometer::update(void) {
  sensors_event_t event;
  sensor.getEvent(&event);

  x = event.acceleration.x;
  y = event.acceleration.y;
  z = event.acceleration.z;
}

/**
 * @return Gets buffered x axis value
 */
float Accelerometer::getX(void) {
  return x;
}

/**
 * @return Gets buffered y axis value
 */
float Accelerometer::getY(void) {
  return y;
}

/**
 * @return Gets buffered z axis value
 */
float Accelerometer::getZ(void) {
  return z;
}
