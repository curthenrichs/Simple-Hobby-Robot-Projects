/**
 * Drivetrain
 * @author Curt Henrichs
 * @date 8-30-17
 *
 * Drivetrain is a software module that defines the tank drive mechanism used
 * for robot locomotion. Relevant mathematical conversions from input space to
 * PWM signals is built into the module so that the drivetrain can appear to
 * act more intuitively. Rational for hiding PWM specifically stems from the
 * Victor SP motor controllers used, which have a specific, experimentally
 * derived range when related to arduino PWM scale. Second is that the module
 * attempts to provide cartesian to differential conversion so that a joystick's
 * x,y coordinates can drive this device.
 *
 * Note that a mechanism to invert one of the motors is built into the math and
 * should not be done externally.
 *
 * Adjusting the tuning parameters should be done sparingly and only to decrease
 * power to motor to bring to match least performant motor.
 */

#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

//==============================================================================
//                               Libraries
//==============================================================================

#include <Arduino.h>

//==============================================================================
//                       Constant and Macro Definitions
//==============================================================================

#define CARTESIAN_RANGE_MIN   -100    //! Full negative direction
#define CARTESIAN_RANGE_MAX    100    //! Full positive direction
#define TANK_RANGE_MIN        -100    //! Full negative direction
#define TANK_RANGE_MAX         100    //! Full positive direction

//==============================================================================
//                         Pulic Function Prototypes
//==============================================================================

/**
 * Intialization function to set drivetrain as an output device and to turn off
 * until commanded.
 * @param leftMotorPWM is pin for the left motor controller
 * @param rightMotorPWM is pin for the right motor controller
 */
void drive_init(unsigned int leftMotorPWM, unsigned int rightMotorPWM);
/**
 * Cartesian drivetrain takes an x and y coordinate pair to drive robot.
 * A transformation for rectangular to polor coordinates is performed meaning
 * heavy use of floating point numbers. Thus this code should not run on just
 * an Arduino.
 * @param x is x-axis value from defined min to max represents amount turning
 * @param y is y-axis value from defined min to max represents amount forward
 * @return true if had to clamp input values down to defined range else false
 */
bool drive_cartesian(int x, int y);
/**
 * Tank drive is left, right motor pair that uses the difference in power to
 * steer.
 * @param l is left motor value from defined min to max
 * @param r is right motor value from defined min to max
 * @param invert (optional) inverts a motor to allow for correct hardware movement
 * @return true if had to clamp input values down to defined range else false
 */
bool drive_tank(int l, int r,bool invert = true);
/**
 * Signals a hard stop which cuts the PWM wave to zero thereby signaling the
 * Victor SP motorcontrollers that the signal has ended.
 */
void drive_hard_stop(void);
/**
 * Sets the pwm for each motor directly without bound checking. Left up to
 * user of function for best practice.
 * @param l is pwm signal on left motor
 * @param r is pwm signal on right motor
 */
void drive_set_pwm(unsigned int l, unsigned int r);

#endif
