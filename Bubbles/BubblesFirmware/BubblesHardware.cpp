/**
 * BubblesHardware
 * @author Curt Henrichs
 * @date 6-24-17
 *
 * Defines and encapsulates Bubbles' hardware structure. Hardware composition,
 *    -> Servo motor to move head up and down.
 *    -> RelayBoard + MotorController to control Bubbles' turning and moving.
 *    -> LEDs to light up Bubbles' eyes and head
 *    -> Ultrasonic sensor to detect distance in front of Bubbles for Autonomous
 *
 * Common functions are implemented such as moving forward, backward, left, and
 * right in order to remove unnecessary multiple functions.
 *
 * Only one BubblesHardware object should be constructed. All other uses should
 * be references to protect the singualr hardware interface.
 */

//==============================================================================
//                                Libraries
//==============================================================================

#include "BubblesHardware.h"

//==============================================================================
//                            Class Implementation
//==============================================================================

/**
 * Constructor initializes Bubbles hardware with the pinout defined in
 * the HardwareConfig.h file. Only one object should be constructed to
 * protect hardware integrity.
 */
BubblesHardware::BubblesHardware(void) :
relayBoard(RELAY_DISABLE_PIN,RELAY_FORWARD_PIN,RELAY_LEFT_PIN,RELAY_RIGHT_PIN),
ultrasonic(ULTRASONIC_PIN),
leds(LED_R_PIN,LED_G_PIN,LED_B_PIN),
motorController(MOTOR_DIRECTION_PIN,MOTOR_STOP_PIN)
{
  neck.attach(NECK_SERVO_PIN);
}

//=============================< Accessors >====================================

/**
 * Gets reference to neck servo motor for neck control.
 * @return reference to Servo object
 */
Servo& BubblesHardware::getNeckServo(void){
  return neck;
}

/**
 * Gets reference to Bubbles RelayBoard
 * @return reference to RelayBoard Object
 */
RelayBoard& BubblesHardware::getRelayBoard(void){
  return relayBoard;
}

/**
 * Gets reference to Bubbles Ultrasonic sensor
 * @return reference to UltrasonicSensor object
 */
UltrasonicSensor& BubblesHardware::getUltrasonic(void){
  return ultrasonic;
}

/**
 * Gets reference to LEDs in Bubbles head
 * @return reference to EyeLED object
 */
EyeLED& BubblesHardware::getLED(void){
  return leds;
}

/**
 * Gets reference to motor controller
 * @return reference to MotorController object
 */
MotorController& BubblesHardware::getMotorController(void){
  return motorController;
}

//=========================< General Control Methods >==========================

/**
 * Commands Bubbles to move forward
 */
void BubblesHardware::forward(void){
  motorController.enable(true);
  motorController.forward();
  relayBoard.forward();
}

/**
 * Commands Bubbles to move backward
 */
void BubblesHardware::backward(void){
  motorController.enable(true);
  motorController.reverse();
  relayBoard.forward();
}

/**
 * Commands Bubbles to turn left and move forward
 */
void BubblesHardware::forwardLeft(void){
  motorController.enable(true);
  motorController.forward();
  relayBoard.left();
}

/**
 * Commands Bubbles to turn right and move forward
 */
void BubblesHardware::forwardRight(void){
  motorController.enable(true);
  motorController.forward();
  relayBoard.right();
}

/**
 * Commands Bubbles to turn right and move backward
 */
void BubblesHardware::backwardRight(void){
  motorController.enable(true);
  motorController.reverse();
  relayBoard.right();
}

/**
 * Commands Bubbles to turn left and move backward
 */
void BubblesHardware::backwardLeft(void){
  motorController.enable(true);
  motorController.reverse();
  relayBoard.left();
}

/**
 * Commands Bubbles to turn right but not move
 */
void BubblesHardware::turnHeadRight(void){
  motorController.enable(false);
  relayBoard.right();
}

/**
 * Commands Bubbles to turn left but not move
 */
void BubblesHardware::turnHeadLeft(void){
  motorController.enable(false);
  relayBoard.left();
}

/**
 * Commands Bubbles to center head for forward movement but not move
 */
void BubblesHardware::centerHead(void){
  motorController.enable(false);
  relayBoard.forward();
}

/**
 * Commands Bubbles to stop moving.
 */
void BubblesHardware::stopMoving(void){
  motorController.enable(false);
  relayBoard.stop();
}

/**
 * Disables control of Bubbles hardware. Hardware will now do its own thing
 * @param disable set disable status
 */
void BubblesHardware::disableControl(bool disable){
  motorController.enable(true);
  motorController.forward();
  relayBoard.disable(disable);
  relayBoard.stop();
}
