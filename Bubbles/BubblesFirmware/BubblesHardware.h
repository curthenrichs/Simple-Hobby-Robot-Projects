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

#ifndef BUBBLESHARDWARE_H
#define BUBBLESHARDWARE_H

//==============================================================================
//                                Libraries
//==============================================================================

#include <Servo.h>
#include "EyeLED.h"
#include <Arduino.h>
#include "RelayBoard.h"
#include "HardwareConfig.h"
#include "MotorController.h"
#include "UltrasonicSensor.h"

//==============================================================================
//                            Class Declaration
//==============================================================================

/**
 * BubblesHardware attempts to define and encapsulate the devices that compose
 * the Bubbles platform. Each component of Bubbles is exposed as a reference
 * from this object. Additionally several general functions are implemented
 * for movement control of Bubbles.
 */
class BubblesHardware {
  private:
    // Controls head position
    Servo neck;
    // Controls Bubbles hardware movement and turning.
    RelayBoard relayBoard;
    // Collects distance in front of Bubbles Head
    UltrasonicSensor ultrasonic;
    // Lights up Bubbles head
    EyeLED leds;
    // Controls the motor in Bubbles drivetrain
    MotorController motorController;

  public:
    /**
     * Constructor initializes Bubbles hardware with the pinout defined in
     * the HardwareConfig.h file. Only one object should be constructed to
     * protect hardware integrity.
     */
    BubblesHardware(void);

//=============================< Accessors >====================================

    /**
     * Gets reference to neck servo motor for neck control.
     * @return reference to Servo object
     */
    Servo& getNeckServo(void);
    /**
     * Gets reference to Bubbles RelayBoard
     * @return reference to RelayBoard Object
     */
    RelayBoard& getRelayBoard(void);
    /**
     * Gets reference to Bubbles Ultrasonic sensor
     * @return reference to UltrasonicSensor object
     */
    UltrasonicSensor& getUltrasonic(void);
    /**
     * Gets reference to LEDs in Bubbles head
     * @return reference to EyeLED object
     */
    EyeLED& getLED(void);
    /**
     * Gets reference to motor controller
     * @return reference to MotorController object
     */
    MotorController& getMotorController(void);

//=========================< General Control Methods >==========================

    /**
     * Commands Bubbles to move forward
     */
    void forward(void);
    /**
     * Commands Bubbles to move backward
     */
    void backward(void);
    /**
     * Commands Bubbles to turn left and move forward
     */
    void forwardLeft(void);
    /**
     * Commands Bubbles to turn right and move forward
     */
    void forwardRight(void);
    /**
     * Commands Bubbles to turn right and move backward
     */
    void backwardRight(void);
    /**
     * Commands Bubbles to turn left and move backward
     */
    void backwardLeft(void);
    /**
     * Commands Bubbles to turn right but not move
     */
    void turnHeadRight(void);
    /**
     * Commands Bubbles to turn left but not move
     */
    void turnHeadLeft(void);
    /**
     * Commands Bubbles to center head for forward movement but not move
     */
    void centerHead(void);
    /**
     * Commands Bubbles to stop moving.
     */
    void stopMoving(void);
    /**
     * Disables control of Bubbles hardware. Hardware will now do its own thing
     * @param disable set disable status
     */
    void disableControl(bool disable);
};

#endif
