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
 
//==============================================================================
//                                  Libraries
//==============================================================================

#include "Display.h"

#include "HardwareConfig.h"
#include <Wire.h>

//==============================================================================
//                         Constant and Macro Definition
//==============================================================================

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

//==============================================================================
//                            Class Implementation
//==============================================================================
/**
 * Constructor creates a new internal display buffer
 */
Display::Display(void) : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1) {
  /* Do nothing */
}

/**
 * Starts I2C comms and sends initial buffer
 */
void Display::begin(void) {
  display.begin(SSD1306_SWITCHCAPVCC, I2C_DISPLAY_ADDRESS);
  display.display();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

/**
 * Clears the OLED display
 */
void Display::clear(void) {
  display.clearDisplay();
}

/**
 * Renders page - Autonomous state
 * @param state is current auton state code
 */
void Display::pageRender_auton(int state) {
  clear();

  display.setCursor(0,0);
  display.print(F("Auton:"));
  display.println(state);
  display.display();
}

/**
 * Renders page - Sensors
 * @param encoderSpeed is current speed from encoder
 * @param distance is current distance cached in ultrasonic
 * @param accX is current acceleration in X direction
 * @param accY is current acceleration in Y direction
 */
void Display::pageRender_sensors(float encoderSpeed, float distance, float accX, float accY) {
  clear();
  display.setCursor(0,0);
  display.print(F("Speed:"));
  display.println(encoderSpeed);
  display.print(F("Dist:"));
  display.println(distance);
  display.print(F("ACC X:"));
  display.print(accX);
  display.print(F(", Y:"));
  display.println(accY);
  display.display();
}

/**
 * Renders page - Motors
 * @param headServo is current value of servo motor
 * @param steerServo is current value of servo motor
 * @param driveMotor is current value of drive motor (+/- is direction)
 */
void Display::pageRender_motors(int headServo, int steerServo, int driveMotor) {
  clear();
  display.setCursor(0,0);
  display.print(F("Head:"));
  display.println(headServo);
  display.print(F("Steer:"));
  display.println(steerServo);
  display.print(F("Drive:"));
  display.println(driveMotor);
  display.display();
}
