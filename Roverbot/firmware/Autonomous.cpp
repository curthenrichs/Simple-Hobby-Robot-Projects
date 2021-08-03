/*
 * Autonomous
 * @author Curt Henrichs
 * @date 7-22-2018
 *
 * Autonomous module defines the state-machine to control Rovebot. The
 * state-machine architecture is built on the switch-case / subroutine
 * 'dispatcher' model. Everything is dependent on timer events running in the
 * main loop so it should be called every main loop tick.
 */

//==============================================================================
//                               Libraries
//==============================================================================

#include "Autonomous.h"

#include "HardwareConfig.h"
#include <elapsedMillis.h>

//==============================================================================
//                         Constant and Macro Definition
//==============================================================================

/**
 * Defines the movement state possible for Bubbles autonomous.
 */
typedef enum TravelState {
  MOVE_FWD,
  MOVE_BWD,
  MOVE_LEFT,
  MOVE_RIGHT,
  HEAD_LEFT,
  HEAD_RIGHT,
  HEAD_CENTER,
  MEASURE_DISTANCE,
  WHICH_WAY_SLCT,
  STUCK_FRONT,
  STUCK_BACK,
  DELAY_FWD_HEAD,
  DELAY_BWD_HEAD,
  ERROR
} TravelState_e;

/**
 * Minimum distance before switching from forward to turning
 */
#define STOPPING_DISTANCE         30
/**
 * Absolute minmimu distance for turning
 */
#define MIN_TURN_RADIUS           15

//Timing constants for physical robot movement
#define FORWARD_TIME              200
#define BACKUP_TIME               1000
#define MOVING_LEFT_TIME          1000
#define MOVING_RIGHT_TIME         1000
#define TURN_HEAD_LEFT_TIME       300
#define TURN_HEAD_RIGHT_TIME      600
#define TURN_HEAD_CENTER_TIME     300
#define DELAY_STUCK_FORWARD       500
#define DELAY_STUCK_BACKWARD      500
#define DELAY_FORWARD             200
#define DELAY_BACKWARD            200

// Maximum allowed delay for stuck states
#define FORWARD_MAX_STUCK_DELAY   5
#define BACKWARD_MAX_STUCK_DELAY  5

// Maxium turn count before considered stuck in corner
#define MAX_LEFT_COUNT            5
#define MAX_RIGHT_COUNT           5

//==============================================================================
//                         Data Structure Declaration
//==============================================================================

/**
 * AI state maintainer used to handle robot stuck cases
 */
typedef struct CornerAI {
  int leftCount = 0;            //! Counts number of left turns
  int rightCount = 0;           //! Counts number of right turns
  int forwardStuckDelay = 1;    //! Increase state time on reentry
  int backwardStuckDelay = 1;   //! Increase state time on reentry
} CornerAI_t;

//==============================================================================
//                             Private Members
//==============================================================================

// state of the autonomous state-machine
static TravelState_e _state;

//timing Variables
static elapsedMillis _delayTimer;

//distance detection storage
static long* _distanceVarPtr = NULL;
static long _leftDist, _rightDist, _centerDist;

// Stuck AI structure to maintain extra-state-machine state
static CornerAI_t ai;

//==============================================================================
//                       Private Function Prototypes
//==============================================================================

/**
 * State MOVE_FWD function move Bubbles forward until min distance is met.
 * then switches to turning head left
 * @param hw is Hardware object to manipulate
 * @return next state (MOVE_FWD or HEAD_LEFT)
 */
static inline TravelState_e _forward(Hardware& hw);

/**
 * State MOVE_BWD function moves Bubbles backward for a predefined amount of
 * time. Switches to turning head left when time elapsed.
 * @param hw is Hardware object to manipulate
 * @return next state (MOVE_BWD or HEAD_LEFT)
 */
static inline TravelState_e _backward(Hardware& hw);

/**
 * State MOVE_LEFT function moves Bubbles left for a predefined amount of
 * time. Switches to moving forward when time elapsed.
 * @param hw is Hardware object to manipulate
 * @return next state (MOVE_LEFT or MOVE_FWD)
 */
static inline TravelState_e _left(Hardware& hw);

/**
 * State MOVE_RIGHT function moves Bubbles right for a predefined amount of
 * time. Switches to moving forward when time elapsed.
 * @param hw is Hardware object to manipulate
 * @return next state (MOVE_RIGHT or MOVE_FWD)
 */
static inline TravelState_e _right(Hardware& hw);

/**
 * State HEAD_LEFT function moves Bubbles head left for a predefined amount of
 * time. Switches to measuring distance after position is reached.
 * @param hw is Hardware object to manipulate
 * @return next state (HEAD_LEFT or MEASURE_DISTANCE)
 */
static inline TravelState_e _headLeft(Hardware& hw);

/**
 * State HEAD_RIGHT function moves Bubbles head right for a predefined amount of
 * time. Switches to measuring distance after postion is reached.
 * @param hw is Hardware object to manipulate
 * @return next state (HEAD_RIGHT or MEASURE_DISTANCE)
 */
static inline TravelState_e _headRight(Hardware& hw);

/**
 * State HEAD_CENTER function moves Bubbles head to center. Switches to
 * measuring distance after position is reached.
 * @param hw is Hardware object o manipulate
 * @return next state (HEAD_CENTER or MEASURE_DISTANCE)
 */
static inline TravelState_e _headCenter(Hardware& hw);

/**
 * State MEASURE_DISTANCE function records the distance from Bubbles to some
 * object. Data is stored in the pointer address that must be specified before
 * this function call. Pointer is then compared with the three known Variables
 * to determine next state of operation.
 * @param hw is Hardware object to manipulate
 * @return next state (HEAD_RIGHT, HEAD_CENTER, WHICH_WAY_SLCT, or ERROR)
 */
static inline TravelState_e _measureDistance(Hardware& hw);

/**
 * State WHICH_WAY_SLCT function to handle the selection of which direction to
 * move Bubbles for the next several states. If the center distance is less than
 * the minimum turning radius then move backward. If left or right distance is
 * less than the minimum turning radius then move backward. Else turn left or
 * right dependign on which is greater.
 * @param hw is Hardware obejct to manipulate
 * @return next state (MOVE_LEFT, MOVE_RIGHT, MOVE_BWD)
 */
static inline TravelState_e _whichWay(Hardware& hw);

/**
 * Backs up on stuck in front
 * @param hw is Hardware object to manipulate
 * @return next state (STUCK_FRONT or MOVE_BWD)
 */
static inline TravelState_e _stuckFront(Hardware& hw);

/**
 * Backs up on stuck in back
 * @param hw is Hardware object to manipulate
 * @return next state (STUCK_BACK or MOVE_FWD)
 */
static inline TravelState_e _stuckBack(Hardware& hw);

/**
 * Delay state between moving forward to head move, used to stop the robot
 * @param hw is Hardware object to manipulate
 * @return next state (HEAD_LEFT)
 */
static inline TravelState_e _delayForwardToHead(Hardware& hw);

/**
 * Delay state between moving backward to head move, used to stop the robot
 * @param hw is Hardware object to manipulate
 * @return next state (HEAD_LEFT)
 */
static inline TravelState_e _delayBackwardToHead(Hardware& hw);

//==============================================================================
//                      Public Function Implementation
//==============================================================================

/**
 * Resets autonomous state-machine. Call once after a need to reset the state
 * machine such as moving from manual operation to autonomous.
 */
void auto_reset(void){
  _state = MOVE_FWD;
  ai.leftCount = 0;
  ai.rightCount = 0;
  ai.forwardStuckDelay = 1;
  ai.backwardStuckDelay = 1;
}

/**
 * Main loop function that will handle the current auton state. This functions
 * could take a large finite amount of time to run due to the nature of the
 * robot.
 * @param hw is Hardware object to manipulate
 */
void auto_update(Hardware& hw){
  // Run current state and update for next update call
  switch(_state){
    case MOVE_FWD:
      _state = _forward(hw);
      break;
    case MOVE_BWD:
      _state = _backward(hw);
      break;
    case MOVE_LEFT:
      _state = _left(hw);
      break;
    case MOVE_RIGHT:
      _state = _right(hw);
      break;
    case HEAD_LEFT:
      _state = _headLeft(hw);
      break;
    case HEAD_CENTER:
      _state = _headCenter(hw);
      break;
    case HEAD_RIGHT:
      _state = _headRight(hw);
      break;
    case MEASURE_DISTANCE:
      _state = _measureDistance(hw);
      break;
    case WHICH_WAY_SLCT:
      _state = _whichWay(hw);
      break;
    case STUCK_FRONT:
      _state = _stuckFront(hw);
        break;
    case STUCK_BACK:
      _state = _stuckBack(hw);
      break;
    case DELAY_FWD_HEAD:
      _state = _delayForwardToHead(hw);
      break;
    case DELAY_BWD_HEAD:
      _state = _delayBackwardToHead(hw);
      break;
    case ERROR:
      hw.stopMoving();
      auto_reset(); // reset state-machine due to error
      break;
    default:
      hw.stopMoving();
      auto_reset(); //something broke, reset state-machine
      break;
  }

  hw.setAutonStateCode(_state);
}

//==============================================================================
//                       Private Function Implementation
//==============================================================================

/**
 * State MOVE_FWD function move Bubbles forward until min distance is met.
 * then switches to turning head left
 * @param hw is Hardware object to manipulate
 * @return next state (MOVE_FWD or HEAD_LEFT)
 */
static inline TravelState_e _forward(Hardware& hw){
  TravelState_e retVal;
  if(_delayTimer >= FORWARD_TIME) {
    long dist = hw.getUltrasonic().getDistance();

    if(dist < STOPPING_DISTANCE){

      //stop the robot going to crash
      hw.stopMoving();

      //start scan for new direction
      retVal = DELAY_FWD_HEAD;

    }else{
      if (hw.isStuck()) {
        hw.stopMoving();
        retVal = STUCK_FRONT;
      } else {
        // move forward as nothing is in the way
        hw.forward();
        retVal = MOVE_FWD;
        ai.forwardStuckDelay = 1;
        ai.backwardStuckDelay = 1;
      }
    }
    _delayTimer = 0;
  }else{
    if (hw.isStuck()) {
      hw.stopMoving();
      retVal = STUCK_FRONT;
      _delayTimer = 0;
    } else {
      // move forward as nothing is in the way
      hw.forward();
      retVal = MOVE_FWD;
      ai.forwardStuckDelay = 1;
      ai.backwardStuckDelay = 1;
    }
  }

  return retVal;
}

/**
 * State MOVE_BWD function moves Bubbles backward for a predefined amount of
 * time. Switches to turning head left when time elapsed.
 * @param hw is Hardware object to manipulate
 * @return next state (MOVE_BWD or HEAD_LEFT)
 */
static inline TravelState_e _backward(Hardware& hw){
  TravelState_e retVal;

  if(_delayTimer >= BACKUP_TIME){
    //done backing up
    hw.stopMoving();

    retVal = DELAY_BWD_HEAD;
    _delayTimer = 0;
  }else{
    if (hw.isStuck()) {
      hw.stopMoving();
      retVal = STUCK_BACK;
      _delayTimer = 0;
    } else {
      // continue backing up
      hw.backward();
      retVal = MOVE_BWD;
      ai.forwardStuckDelay = 1;
      ai.backwardStuckDelay = 1;
    }
  }
  return retVal;
}

/**
 * State MOVE_LEFT function moves Bubbles left for a predefined amount of
 * time. Switches to moving forward when time elapsed.
 * @param hw is Hardware object to manipulate
 * @return next state (MOVE_LEFT or MOVE_FWD)
 */
static inline TravelState_e _left(Hardware& hw){
  TravelState_e retVal;
  if(_delayTimer >= MOVING_LEFT_TIME){
    //done turning left
    retVal = MOVE_FWD;
    _delayTimer = 0;
  }else{
    //continue turning left
    hw.forwardLeft();
    retVal = MOVE_LEFT;
  }
  return retVal;
}

/**
 * State MOVE_RIGHT function moves Bubbles right for a predefined amount of
 * time. Switches to moving forward when time elapsed.
 * @param hw is Hardware object to manipulate
 * @return next state (MOVE_RIGHT or MOVE_FWD)
 */
static inline TravelState_e _right(Hardware& hw){
  TravelState_e retVal;
  if(_delayTimer >= MOVING_RIGHT_TIME){
    //done turning right
    retVal = MOVE_FWD;
    _delayTimer = 0;
  }else{
    //continue turning right
    hw.forwardRight();
    retVal = MOVE_RIGHT;
  }
  return retVal;
}

/**
 * State HEAD_LEFT function moves Bubbles head left for a predefined amount of
 * time. Switches to measuring distance after position is reached.
 * @param hw is Hardware object to manipulate
 * @return next state (HEAD_LEFT or MEASURE_DISTANCE)
 */
static inline TravelState_e _headLeft(Hardware& hw){
  TravelState_e retVal;
  if(_delayTimer >= TURN_HEAD_LEFT_TIME){
    //done turning head left
    hw.stopMoving();
    _distanceVarPtr = &_leftDist;
    retVal = MEASURE_DISTANCE;
    _delayTimer = 0;
  }else{
    //continue turing head left
    hw.turnHeadLeft();
    retVal = HEAD_LEFT;
  }
  return retVal;
}

/**
 * State HEAD_RIGHT function moves Bubbles head right for a predefined amount of
 * time. Switches to measuring distance after postion is reached.
 * @param hw is Hardware object to manipulate
 * @return next state (HEAD_RIGHT or MEASURE_DISTANCE)
 */
static inline TravelState_e _headRight(Hardware& hw){
  TravelState_e retVal;
  if(_delayTimer >= TURN_HEAD_RIGHT_TIME){
    //done turning head right
    hw.stopMoving();
    _distanceVarPtr = &_rightDist;
    retVal = MEASURE_DISTANCE;
    _delayTimer = 0;
  }else{
    //continue turing head right
    hw.turnHeadRight();
    retVal = HEAD_RIGHT;
  }
  return retVal;
}

/**
 * State HEAD_CENTER function moves Bubbles head to center. Switches to
 * measuring distance after position is reached.
 * @param hw is Hardware object o manipulate
 * @return next state (HEAD_CENTER or MEASURE_DISTANCE)
 */
static inline TravelState_e _headCenter(Hardware& hw){
  TravelState_e retVal;
  if(_delayTimer >= TURN_HEAD_CENTER_TIME){
    //done turning head to center
    hw.stopMoving();
    _distanceVarPtr = &_centerDist;
    retVal = MEASURE_DISTANCE;
    _delayTimer = 0;
  }else{
    //contine turing head to center
    hw.centerHead();
    retVal = HEAD_CENTER;
  }
  return retVal;
}

/**
 * State MEASURE_DISTANCE function records the distance from Bubbles to some
 * object. Data is stored in the pointer address that must be specified before
 * this function call. Pointer is then compared with the three known Variables
 * to determine next state of operation.
 * @param hw is Hardware object to manipulate
 * @return next state (HEAD_RIGHT, HEAD_CENTER, WHICH_WAY_SLCT, or ERROR)
 */
static inline TravelState_e _measureDistance(Hardware& hw){
  TravelState_e retVal;
  if(_distanceVarPtr == NULL){
    return ERROR;
  }

  //get distance and select next state
  *_distanceVarPtr = hw.getUltrasonic().getDistance();
  if(_distanceVarPtr == &_leftDist){
    //turn head right
    retVal = HEAD_RIGHT;
  }else if(_distanceVarPtr == &_rightDist){
    //turn head to center
    retVal = HEAD_CENTER;
  }else if(_distanceVarPtr == &_centerDist){
    //determine which way to travel
    retVal = WHICH_WAY_SLCT;
  }else{
    //error occured
    retVal = ERROR;
  }
  _delayTimer = 0;
  return retVal;
}

/**
 * State WHICH_WAY_SLCT function to handle the selection of which direction to
 * move Bubbles for the next several states. If the center distance is less than
 * the minimum turning radius then move backward. If left or right distance is
 * less than the minimum turning radius then move backward. Else turn left or
 * right dependign on which is greater.
 * @param hw is Hardware obejct to manipulate
 * @return next state (MOVE_LEFT, MOVE_RIGHT, MOVE_BWD)
 */
static inline TravelState_e _whichWay(Hardware& hw){
  TravelState_e retVal;

  if (ai.rightCount > MAX_RIGHT_COUNT || ai.leftCount > MAX_LEFT_COUNT) {
    ai.rightCount = 0;
    ai.leftCount = 0;
    retVal = MOVE_BWD;
  } else {
    if(_centerDist < MIN_TURN_RADIUS){
      retVal = MOVE_BWD;
    }else if(_leftDist < MIN_TURN_RADIUS && _rightDist < MIN_TURN_RADIUS){
      retVal = MOVE_BWD;
    }else if(_leftDist >= _rightDist){
      retVal = MOVE_LEFT;
      ai.leftCount++;
    }else{
      ai.rightCount++;
      retVal = MOVE_RIGHT;
    }
  }

  _delayTimer = 0;
  return retVal;
}

/**
 * Backs up on stuck in front
 * @param hw is Hardware object to manipulate
 * @return next state (STUCK_FRONT or MOVE_BWD)
 */
static inline TravelState_e _stuckFront(Hardware& hw){
  TravelState_e retVal;

  // move backward
  if (_delayTimer >= (DELAY_STUCK_FORWARD * ai.forwardStuckDelay)) {

    ai.forwardStuckDelay += 1;
    if (ai.forwardStuckDelay > FORWARD_MAX_STUCK_DELAY) {
      ai.forwardStuckDelay = FORWARD_MAX_STUCK_DELAY;
    }

    retVal = MOVE_BWD;
    _delayTimer = 0;
  } else {
    hw.backward();
    retVal = STUCK_FRONT;
  }

  return retVal;
}

/**
 * Backs up on stuck in back
 * @param hw is Hardware object to manipulate
 * @return next state (STUCK_BACK or MOVE_FWD)
 */
static inline TravelState_e _stuckBack(Hardware& hw){
  TravelState_e retVal;

  if (_delayTimer >= (DELAY_STUCK_BACKWARD * ai.backwardStuckDelay)) {

    ai.backwardStuckDelay += 1;
    if (ai.backwardStuckDelay > BACKWARD_MAX_STUCK_DELAY) {
      ai.backwardStuckDelay = BACKWARD_MAX_STUCK_DELAY;
    }

    retVal = MOVE_FWD;
    _delayTimer = 0;
  } else {
    hw.forward();
    retVal = STUCK_BACK;
  }

  return retVal;
}

/**
 * Delay state between moving forward to head move, used to stop the robot
 * @param hw is Hardware object to manipulate
 * @return next state (HEAD_LEFT)
 */
static inline TravelState_e _delayForwardToHead(Hardware& hw){
  TravelState_e retval;

  if (_delayTimer >= DELAY_FORWARD) {
    retval = HEAD_LEFT;
    _delayTimer = 0;
  } else {
    retval = DELAY_FWD_HEAD;
  }

  return retval;
}

/**
 * Delay state between moving backward to head move, used to stop the robot
 * @param hw is Hardware object to manipulate
 * @return next state (HEAD_LEFT)
 */
static inline TravelState_e _delayBackwardToHead(Hardware& hw){
  TravelState_e retval;

  if (_delayTimer >= DELAY_BACKWARD) {
    retval = HEAD_LEFT;
    _delayTimer = 0;
  } else {
    retval = DELAY_BWD_HEAD;
  }

  return retval;
}
