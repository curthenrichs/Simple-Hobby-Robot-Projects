/**
 * Hardware
 * @author Curt Henrichs
 * @date 7-22-2018
 *
 * Robot hardware layer aggregates the low-level hardware drivers into a single
 * interface for use in the autonomous layer.
 */
 
#ifndef HARDWARE_H
#define HARDWARE_H

//==============================================================================
//                                Libraries
//==============================================================================

#include <Servo.h>
#include "HardwareConfig.h"
#include "MotorController.h"
#include "UltrasonicSensor.h"
#include <elapsedMillis.h>
#include "Encoder.h"

//==============================================================================
//                         Data Structure Declaration
//==============================================================================

/**
 * Bang-bang closed loop speed controller which tries to stay within a speed
 * bin.
 */
typedef struct SpeedController {
  bool isCommandedToMove;       //! Robot should be moving
  int appearsStuckCount;        //! Number of times speed was classified as stuck
  elapsedMillis updateTimer;    //! Time event to update controller state
  int8_t speedOffset;           //! Offset on the drive motor PWM
} SpeedController_t;

//==============================================================================
//                            Class Declaration
//==============================================================================

/**
 * Defines generalized hardware for the robot so that an autonomous layer can
 * interface with it in a reusable manner.
 */
class Hardware {

  private:
    UltrasonicSensor ultrasonic;        //! Reference to head sensor
    MotorController motorController;    //! Reference to drive motor
    Servo head;                         //! Reference to head motor
    Servo steering;                     //! Reference to steer motor
    SpeedController_t speedController;  //! Reference to speed controller
    Encoder encoder;                    //! Reference to speed sensor

    /**
     * Computes new state of the speed controller on timing event
     */
    void _updateSpeedController(void);

  public:
    /**
     * Constructor initializes Roverbot's hardware with the pinout defined in
     * the HardwareConfig.h file. Only one object should be constructed to
     * protect hardware integrity.
     */
    Hardware(void);
    /**
     * Gets reference to head servo motor for head position control.
     * @return reference to Servo object
     */
    Servo& getHeadServo(void);
    /**
     * Gets reference to steer servo motor for steering direction control.
     * @return reference to Servo object
     */
    Servo& getSteerServo(void);
    /**
     * Gets reference to Roverbot's Ultrasonic sensor
     * @return reference to UltrasonicSensor object
     */
    UltrasonicSensor& getUltrasonic(void);
    /**
     * Gets reference to motor controller
     * @return reference to MotorController object
     */
    MotorController& getMotorController(void);
    /**
     * Sets up interface with hardware, as constructor is called before hardware
     * in enumerated, thus an error occurs.
     */
    void begin(void);
    /**
     * Periodic update (should be called every main loop). Handles any hardware
     * events.
     */
    void update(void);
    /**
     * Commands Roverbot's to move forward
     */
    void forward(void);
    /**
     * Commands Roverbot's to move backward
     */
    void backward(void);
    /**
     * Commands Roverbot's to turn left and move forward
     */
    void forwardLeft(void);
    /**
     * Commands Roverbot's to turn right and move forward
     */
    void forwardRight(void);
    /**
     * Commands Roverbot's to turn right and move backward
     */
    void backwardRight(void);
    /**
     * Commands Roverbot's to turn left and move backward
     */
    void backwardLeft(void);
    /**
     * Commands Roverbot's to turn right but not move
     */
    void turnHeadRight(void);
    /**
     * Commands Roverbot's to turn left but not move
     */
    void turnHeadLeft(void);
    /**
     * Commands Roverbot's to center head for forward movement but not move
     */
    void centerHead(void);
    /**
     * Commands Roverbot's to stop moving.
     */
    void stopMoving(void);
    /**
     * @return true if the robot thinks it is stuck else false
     */
    bool isStuck(void);
};

#endif