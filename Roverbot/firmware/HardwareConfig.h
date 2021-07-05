/*
 * HardwareConfig
 * @author Curt Henrichs
 * @date 7-22-2018
 *
 * Hardware configuration file defines hardware layout.
 *
 * Note pins A0, A1 are broken on the UNO 3 I am currently using.
 */

#ifndef HARDWARECONFIG_H
#define HARDWARECONFIG_H

//==============================================================================
//                               Libraries
//==============================================================================

#include <Arduino.h>

//==============================================================================
//                              Device Pinout
//==============================================================================

#define HW_SERIAL_RX_PIN                    0
#define HW_SERIAL_TX_PIN                    1
#define ULTRASONIC_PIN                      7
#define STEER_SERVO_PIN                     5
#define HEAD_SERVO_PIN                      6
#define MOTOR_CONTROLLER_BRAKE_PIN          9
#define MOTOR_CONTROLLER_DIRECTION_PIN      12
#define MOTOR_CONTROLLER_PWM_PIN            3
#define ENCODER_PIN                         A3

#define DONT_USE_A0_PIN                     A0
#define DONT_USE_A1_PIN                     A1

//==============================================================================
//                              Debug Serial
//==============================================================================

#define DEBUG_SERIAL                        Serial
#define DEBUG_SERIAL_BAUD                   9600

#endif
