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
    Adafruit_LIS3DH sensor;   //! internal I2C sensor interface
    float x, y, z;            //! cached sensor readings

  public:
    /**
     * Constructor creates a new sensor
     */
    Accelerometer(void);
    /**
     * Starts I2C comms
     */
    void begin(void);
    /**
     * Queries the I2C device for latest state
     */
    void update(void);
    /**
     * @return Gets buffered x axis value
     */
    float getX(void);
    /**
     * @return Gets buffered y axis value
     */
    float getY(void);
    /**
     * @return Gets buffered z axis value
     */
    float getZ(void);
};

#endif
