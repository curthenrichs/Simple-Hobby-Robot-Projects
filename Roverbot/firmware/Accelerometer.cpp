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

Accelerometer::Accelerometer(void) : sensor() {
  x = 0;
  y = 0;
  z = 0;
}

void Accelerometer::begin(void) {
  sensor.begin(I2C_ACCEROMETER_ADDRESS);
}

void Accelerometer::update(void) {
  sensors_event_t event;
  sensor.getEvent(&event);

  x = event.acceleration.x;
  y = event.acceleration.y;
  z = event.acceleration.z;
}

float Accelerometer::getX(void) {
  return x;
}

float Accelerometer::getY(void) {
  return y;
}

float Accelerometer::getZ(void) {
  return z;
}
