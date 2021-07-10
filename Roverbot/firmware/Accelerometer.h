/**
 * Accelerometer
 * @author Curt Henrichs
 * @date 7-7-21
 * 
 * Thin wrapper around Adafruit accelerometer library. Used to extract
 * the relevant data for roverbot.
 */

#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

//==============================================================================
//                                  Libraries
//==============================================================================

#include <Arduino.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

//==============================================================================
//                            Class Declaration
//==============================================================================

class Accelerometer {

  private:
    Adafruit_LIS3DH sensor;
    float x, y, z;

  public:

    Accelerometer(void);

    void begin(void);

    void update(void);

    float getX(void);

    float getY(void);

    float getZ(void);
};

#endif
