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

//==============================================================================
//                               Libraries
//==============================================================================

#include "Drivetrain.h"
#include "HardwareConfig.h"
#include <math.h>

//==============================================================================
//                       Constant and Macro Definitions
//==============================================================================

/*
 * Experimentally derived PWM range for Victor SP motor controllers
 */
#define PWM_NEG_MAX 82   //! Lower limt turns in negaitve direction
#define PWM_POS_MAX 172   //! Upper limit turns in positive direction

//==============================================================================
//                           Private Attributes
//==============================================================================

/**
 * Assigned pin connected to left motor controller
 */
static unsigned int _leftMotorPWM;
/**
 * Assigned pin connected to right motor controller
 */
static unsigned int _rightMotorPWM;
/**
 * Drive status of the motors. True if a motor is moving else False
 */
static bool _active = false;

//==============================================================================
//                      Public Function Implementation
//==============================================================================

/**
 * Intialization function to set drivetrain as an output device and to turn off
 * until commanded.
 * @param leftMotorPWM is pin for the left motor controller
 * @param rightMotorPWM is pin for the right motor controller
 */
void drive_init(unsigned int leftMotorPWM, unsigned int rightMotorPWM){
  analogWriteRange(256);
  analogWriteFreq(333);
  pinMode(leftMotorPWM,OUTPUT);
  pinMode(rightMotorPWM,OUTPUT);
  _leftMotorPWM = leftMotorPWM;
  _rightMotorPWM = rightMotorPWM;
  drive_hard_stop();
}

/**
 * Cartesian drivetrain takes an x and y coordinate pair to drive robot.
 * A transformation for rectangular to polor coordinates is performed meaning
 * heavy use of floating point numbers. Thus this code should not run on just
 * an Arduino.
 * @param x is x-axis value from defined min to max represents amount turning
 * @param y is y-axis value from defined min to max represents amount forward
 * @return true if had to clamp input values down to defined range else false
 */
bool drive_cartesian(int x, int y){
  //bound clamping
  bool clamped = false;
  if(x > CARTESIAN_RANGE_MAX){
    x = CARTESIAN_RANGE_MAX;
    clamped = true;
  }else if(x < CARTESIAN_RANGE_MIN){
    x = CARTESIAN_RANGE_MIN;
    clamped = true;
  }
  if(y > CARTESIAN_RANGE_MAX){
    y = CARTESIAN_RANGE_MAX;
    clamped = true;
  }else if(y < CARTESIAN_RANGE_MIN){
    y = CARTESIAN_RANGE_MIN;
    clamped = true;
  }
  x *= -1; //invert x for math to work out

  //convert to polar cooardinates
  float radius = sqrt(pow(x,2) + pow(y,2));
  float angle = atan2(y,x);

  //rotate 45 degrees (for diamond coordinates)
  angle += PI / 4;
  float dl = radius * cos(angle);
  float dr = radius * sin(angle);

#if DEBUGGING_MODE
  Serial.print("X input: ");
  Serial.print(x);
  Serial.print(", Y input: ");
  Serial.println(y);
  Serial.print("Polar Form of inputs, r: ");
  Serial.print(radius);
  Serial.print(", a: ");
  Serial.println(angle);
  Serial.print("Left output: ");
  Serial.print(dl);
  Serial.print(", Right output: ");
  Serial.println(dr);
#endif

  //drive tank
  drive_tank(dl,dr,false);

  return clamped;
}

/**
 * Tank drive is left, right motor pair that uses the difference in power to
 * steer.
 * @param l is left motor value from defined min to max
 * @param r is right motor value from defined min to max
 * @param invert (optional) inverts a motor to allow for correct hardware movement
 * @return true if had to clamp input values down to defined range else false
 */
bool drive_tank(int l, int r, bool invert){
  //bound clamping
  bool clamped = false;
  if(l > TANK_RANGE_MAX){
    l = TANK_RANGE_MAX;
    clamped = true;
  }else if(l < TANK_RANGE_MIN){
    l = TANK_RANGE_MIN;
    clamped = true;
  }
  if(r > TANK_RANGE_MAX){
    r = TANK_RANGE_MAX;
    clamped = true;
  }else if(r < TANK_RANGE_MIN){
    r = TANK_RANGE_MIN;
    clamped = true;
  }

  //convert to PWM signal
  float pwm_slope = (PWM_POS_MAX - PWM_NEG_MAX)/((TANK_RANGE_MAX - TANK_RANGE_MIN)*1.0f);
  float pwm_inter = PWM_POS_MAX - pwm_slope * TANK_RANGE_MAX;
  unsigned int l_pwm = (unsigned int)(l * pwm_slope * (invert ? -1 : 1) * ((l < 0) ? 0.9f : 1) + pwm_inter);
  unsigned int r_pwm = (unsigned int)(r * pwm_slope * ((r < 0) ? 0.9f : 1) + pwm_inter);

#if DEBUGGING_MODE
  Serial.print("PWM Slope: ");
  Serial.print(pwm_slope);
  Serial.print(", PWM Intercept: ");
  Serial.println(pwm_inter);
  Serial.print("Left Input: ");
  Serial.print(l);
  Serial.print(", Left PWM: ");
  Serial.println(l_pwm);
  Serial.print("Right Input: ");
  Serial.print(r);
  Serial.print(", Right PWM: ");
  Serial.println(r_pwm);
#endif

  //set PWM
  drive_set_pwm(l_pwm,r_pwm);

  return clamped;
}

/**
 * Signals a hard stop which cuts the PWM wave to zero thereby signaling the
 * Victor SP motorcontrollers that the signal has ended.
 */
void drive_hard_stop(void){
  drive_tank(0,0);
}

/**
 * Sets the pwm for each motor directly without bound checking. Left up to
 * user of function for best practice.
 * @param l is pwm signal on left motor
 * @param r is pwm signal on right motor
 */
void drive_set_pwm(unsigned int l, unsigned int r){
  analogWrite(_leftMotorPWM,l);
  analogWrite(_rightMotorPWM,r);
}
