/**
 * Display
 * @author Curt Henrichs
 * @date 7-7-21
 * 
 * Display provides a thin wrapper around the adafruit OLED library. Several
 * pages are layed out (each as a function) that can easily draw the robot's
 * state information. This module is mainly for debugging while disconnected
 * from the PC.
 */

#ifndef DISPLAY_H
#define DISPLAY_H

//==============================================================================
//                                  Libraries
//==============================================================================

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//==============================================================================
//                            Class Declaration
//==============================================================================

class Display {

  private:
    Adafruit_SSD1306 display; //! Internal buffer and comm logic

  public:
    /**
     * Constructor creates a new internal display buffer
     */
    Display(void);
    /**
     * Starts I2C comms and sends initial buffer
     */
    void begin(void);
    /**
     * Clears the OLED display
     */
    void clear(void);
    /**
     * Renders page - Autonomous state
     * @param state is current auton state code
     */
    void pageRender_auton(int state);
    /**
     * Renders page - Sensors
     * @param encoderSpeed is current speed from encoder
     * @param distance is last read distance from ultrasonic
     * @param accX is current acceleration in X direction
     * @param accY is current acceleration in Y direction
     */
    void pageRender_sensors(int encoderSpeed, int distance, int accX, int accY);
    /**
     * Renders page - Motors
     * @param headServo is current value of servo motor
     * @param steerServo is current value of servo motor
     * @param driveMotor is current value of drive motor (+/- is direction)
     */
    void pageRender_motors(int headServo, int steerServo, int driveMotor);
};


#endif
