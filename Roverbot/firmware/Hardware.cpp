/**
 * Hardware
 * @author Curt Henrichs
 * @date 7-22-2018
 *
 * Robot hardware layer aggregates the low-level hardware drivers into a single
 * interface for use in the autonomous layer.
 */

//==============================================================================
//                                Libraries
//==============================================================================

#include "Hardware.h"
#include <math.h>

//==============================================================================
//                       Constants and Macro Definitions
//==============================================================================

//Steering Servo constants
#define STEER_SERVO_CENTER                 85  //degrees
#define STEER_SERVO_LEFT                   110 //degrees
#define STEER_SERV0_RIGHT                  60  //degrees

//Head Servo constants
#define HEAD_SERVO_CENTER                  85  //degrees
#define HEAD_SERVO_LEFT                    50  //degrees
#define HEAD_SERVO_RIGHT                   120 //degrees

//Default motor speeds
#define MOTOR_REVERSE_SPEED                 190 //pwm
#define MOTOR_FORWARD_SPEED                 160 //pwm
#define MOTOR_FORWARD_TURN_SPEED            200 //pwm

// Different categories of speed used to classiy accelerometer output
typedef enum SpeedBins {
  SPEED_STUCK,      //! Speed is approximatly zero and should not be
  SPEED_SLOW,       //! Speed could be higher
  SPEED_NORMAL,     //! Speed is just right :}
  SPEED_HIGH,       //! Speed could be lower
  SPEED_INVALID     //! Speed is not zero and should be
} SpeedBins_t;

// Speed controller update constants
#define STUCK_COUNT_THRESHOLD               5
#define UPDATE_SPEED_CONTROLLER_TIME        200 //ms

//==============================================================================
//                            Class Implementation
//==============================================================================

/**
 * Constructor initializes Bubbles hardware with the pinout defined in
 * the HardwareConfig.h file. Only one object should be constructed to
 * protect hardware integrity.
 */
Hardware::Hardware(void) : motorController(MOTOR_CONTROLLER_DIRECTION_PIN,
                                           MOTOR_CONTROLLER_BRAKE_PIN,
                                           MOTOR_CONTROLLER_PWM_PIN),
                           ultrasonic(ULTRASONIC_PIN),
                           encoder(ENCODER_PIN),
                           display()
{
  speedController.isCommandedToMove = false;
  speedController.appearsStuckCount = 0;
  speedController.updateTimer = 0;
  speedController.speedOffset = 0;
}

/**
 * Gets reference to head servo motor for head position control.
 * @return reference to Servo object
 */
Servo& Hardware::getHeadServo(void){
  return head;
}

/**
 * Gets reference to steer servo motor for steering direction control.
 * @return reference to Servo object
 */
Servo& Hardware::getSteerServo(void){
  return steering;
}

/**
 * Gets reference to Roverbot's Ultrasonic sensor
 * @return reference to UltrasonicSensor object
 */
UltrasonicSensor& Hardware::getUltrasonic(void){
  return ultrasonic;
}

/**
 * Gets reference to motor controller
 * @return reference to MotorController object
 */
MotorController& Hardware::getMotorController(void){
  return motorController;
}

/**
 * Gets reference to display
 * @return reference to Display object
 */
Display& Hardware::getDisplay(void){
  return display; 
}

/**
 * Get reference to accelerometer
 * @return reference to Accelerometer object
 */
Accelerometer& Hardware::getAccelerometer(void){
  return accelerometer;
}

/**
 * Sets up interface with hardware, as constructor is called before hardware
 * in enumerated, thus an error occurs.
 */
void Hardware::begin(void){
  head.attach(HEAD_SERVO_PIN);
  head.write(HEAD_SERVO_CENTER);
  steering.attach(STEER_SERVO_PIN);
  steering.write(STEER_SERVO_CENTER);
  encoder.init();

  ultrasonic.begin();
  accelerometer.begin();
  motorController.begin();
  display.begin();
}

/**
 * Periodic update (should be called every main loop). Handles any hardware
 * events.
 */
void Hardware::update(void){
  encoder.update();

  accelerometer.update();

  if (speedController.updateTimer >= UPDATE_SPEED_CONTROLLER_TIME) {
    speedController.updateTimer -= UPDATE_SPEED_CONTROLLER_TIME;
    _updateSpeedController();
  }
}

/**
 * Commands Roverbot's to move forward
 */
void Hardware::forward(void){
  speedController.isCommandedToMove = true;
  steering.write(STEER_SERVO_CENTER);
  motorController.forward(MOTOR_FORWARD_SPEED + speedController.speedOffset);
}

/**
 * Commands Roverbot's to move backward
 */
void Hardware::backward(void){
  speedController.isCommandedToMove = true;
  steering.write(STEER_SERVO_CENTER);
  motorController.reverse(MOTOR_REVERSE_SPEED + speedController.speedOffset);
}

/**
 * Commands Roverbot's to turn left and move forward
 */
void Hardware::forwardLeft(void){
  speedController.isCommandedToMove = true;
  steering.write(STEER_SERVO_LEFT);
  motorController.forward(MOTOR_FORWARD_TURN_SPEED + speedController.speedOffset);
}

/**
 * Commands Roverbot's to turn right and move forward
 */
void Hardware::forwardRight(void){
  speedController.isCommandedToMove = true;
  steering.write(STEER_SERV0_RIGHT);
  motorController.forward(MOTOR_FORWARD_TURN_SPEED + speedController.speedOffset);
}

/**
 * Commands Roverbot's to turn right and move backward
 */
void Hardware::backwardRight(void){
  speedController.isCommandedToMove = true;
  steering.write(STEER_SERVO_LEFT);
  motorController.reverse(MOTOR_REVERSE_SPEED + speedController.speedOffset);
}

/**
 * Commands Roverbot's to turn left and move backward
 */
void Hardware::backwardLeft(void){
  speedController.isCommandedToMove = true;
  steering.write(STEER_SERV0_RIGHT);
  motorController.reverse(MOTOR_REVERSE_SPEED + speedController.speedOffset);
}

/**
 * Commands Roverbot's to turn right but not move
 */
void Hardware::turnHeadRight(void){
  head.write(HEAD_SERVO_RIGHT);
}

/**
 * Commands Roverbot's to turn left but not move
 */
void Hardware::turnHeadLeft(void){
  head.write(HEAD_SERVO_LEFT);
}

/**
 * Commands Roverbot's to center head for forward movement but not move
 */
void Hardware::centerHead(void){
  head.write(HEAD_SERVO_CENTER);
}

/**
 * Commands Roverbot's to stop moving.
 */
void Hardware::stopMoving(void){
  speedController.isCommandedToMove = false;
  motorController.stop();
}

/**
 * @return true if the robot thinks it is stuck else false
 */
bool Hardware::isStuck(void) {
  return speedController.appearsStuckCount >= STUCK_COUNT_THRESHOLD;
}

/**
 * Computes new state of the speed controller on timing event
 */
void Hardware::_updateSpeedController(void) {

  // classify
  float speed = encoder.getSpeed();
  SpeedBins_t bin;
  if (speedController.isCommandedToMove) {
    if (speed <= 0.5) {
      bin = SPEED_STUCK;
    } else if (speed <= 5) {
      bin = SPEED_SLOW;
    } else if (speed <= 8) {
      bin = SPEED_NORMAL;
    } else {
      bin = SPEED_HIGH;
    }
  } else {
    if (speed > 0.5) {
      bin = SPEED_INVALID;
    } else {
      bin = SPEED_NORMAL;
    }
  }

  // compute stuck
  if (bin == SPEED_STUCK) {
    speedController.appearsStuckCount += 1;
    if (speedController.appearsStuckCount > STUCK_COUNT_THRESHOLD) {
      speedController.appearsStuckCount = STUCK_COUNT_THRESHOLD;
    }
  } else {
    speedController.appearsStuckCount -= 1;
    if (speedController.appearsStuckCount < 0) {
      speedController.appearsStuckCount = 0;
    }
  }

  // compute speed offset
  if (bin == SPEED_SLOW || bin == SPEED_STUCK) {
    speedController.speedOffset += 10;
    if (speedController.speedOffset >= 50) {
      speedController.speedOffset = 50;
    }
  } else if (bin == SPEED_HIGH) {
    speedController.speedOffset -= 10;
    if (speedController.speedOffset <= -10) {
      speedController.speedOffset = -10;
    }
  } else if (bin == SPEED_INVALID) {
    speedController.speedOffset = 0;
  }
}
