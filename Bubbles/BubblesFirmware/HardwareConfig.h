/**
 * HardwareConfig
 * @author Curt Henrichs
 * @date 6-24-17
 *
 * Hardware configuration file defines the pinout of the platform in addditon to
 * defining common constants used for program executation.
 *
 * Pinout:
 *    -> 0  Serial RX
 *    -> 1  Serial TX
 *    -> 2  XBee RX
 *    -> 3  Neck Servo (PWM)
 *    -> 4  Relay
 *    -> 5  Relay
 *    -> 6  Relay
 *    -> 7  Relay
 *    -> 8  XBee TX
 *    -> 9  Red LED Channel (PWM)
 *    -> 10 Green LED Channel (PWM)
 *    -> 11 Blue LED Channel (PWM)
 *    -> 12 Motor Diretion
 *    -> 13 Ultrasonic 
 *    -> A0 Motor Stop
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

#define SERIAL_RX_PIN                 0
#define SERIAL_TX_PIN                 1
#define XBEE_RX_PIN                   2
#define XBEE_TX_PIN                   8
#define RELAY_DISABLE_PIN             7
#define RELAY_FORWARD_PIN             5
#define RELAY_LEFT_PIN                6
#define RELAY_RIGHT_PIN               4
#define MOTOR_DIRECTION_PIN           12
#define MOTOR_STOP_PIN                A0
#define ULTRASONIC_PIN                13
#define LED_R_PIN                     9
#define LED_G_PIN                     11
#define LED_B_PIN                     10
#define NECK_SERVO_PIN                3

//==============================================================================
//                          Constant and Macro Definition
//==============================================================================

#define XBEE_BAUD                     9600
#define NECK_MIN_POS                  0
#define NECK_MAX_POS                  120

#endif
