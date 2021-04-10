/**
 * HardwareConfig
 * @author Curt Henrichs
 * @date 9-1-17
 *
 * Hardware Configuration file used to control conditional compilation and
 * physical device mapping for applicaiton abstraction.
 */

#ifndef HARDWARECONFIG_H
#define HARDWARECONFIG_H

//==============================================================================
//                               Libraries
//==============================================================================

#include <Arduino.h>

//==============================================================================
//                           Compile Configuration
//==============================================================================

#define DEBUGGING_MODE true  //! User configurable option to toggle debug print

//==============================================================================
//                             Device Pinout
//==============================================================================

#define LEFT_MOTOR_PIN    D5  // PWM pin
#define RIGHT_MOTOR_PIN   D6  // PWM pin

#endif
