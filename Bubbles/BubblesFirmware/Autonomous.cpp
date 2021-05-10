/**
 * Autonomous
 * @author Curt Henrichs
 * @date 6-24-17
 *
 * Autonomous control of Bubbles uses a "wall-banger" random wandering
 * algorithm to go to no place in particular. The code runs as a main-loop
 * state machine as is dependent on having update called regularly.
 */

//==============================================================================
//                               Libraries
//==============================================================================

#include "Autonomous.h"
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
  ERROR
} TravelState_e;

/**
 * Minimum distance before switching from forward to turning
 */
#define STOPPING_DISTANCE 40
/**
 * Absolute minmimu distance for turning
 */
#define MIN_TURN_RADIUS 30

//Timing constants for physical robot movement
#define BACKUP_TIME 5000
#define MOVING_LEFT_TIME 10000
#define MOVING_RIGHT_TIME 10000
#define TURN_HEAD_LEFT_TIME 4000
#define TURN_HEAD_RIGHT_TIME 8000
#define TURN_HEAD_CENTER_TIME 4000

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

//==============================================================================
//                       Private Function Prototypes
//==============================================================================

/**
 * State MOVE_FWD function move Bubbles forward until min distance is met.
 * then switches to turning head left
 * @param hw is BubblesHardware object to manipulate
 * @return next state (MOVE_FWD or HEAD_LEFT)
 */
static inline TravelState_e _forward(BubblesHardware& hw);

/**
 * State MOVE_BWD function moves Bubbles backward for a predefined amount of
 * time. Switches to turning head left when time elapsed.
 * @param hw is BubblesHardware object to manipulate
 * @return next state (MOVE_BWD or HEAD_LEFT)
 */
static inline TravelState_e _backward(BubblesHardware& hw);

/**
 * State MOVE_LEFT function moves Bubbles left for a predefined amount of
 * time. Switches to moving forward when time elapsed.
 * @param hw is BubblesHardware object to manipulate
 * @return next state (MOVE_LEFT or MOVE_FWD)
 */
static inline TravelState_e _left(BubblesHardware& hw);

/**
 * State MOVE_RIGHT function moves Bubbles right for a predefined amount of
 * time. Switches to moving forward when time elapsed.
 * @param hw is BubblesHardware object to manipulate
 * @return next state (MOVE_RIGHT or MOVE_FWD)
 */
static inline TravelState_e _right(BubblesHardware& hw);

/**
 * State HEAD_LEFT function moves Bubbles head left for a predefined amount of
 * time. Switches to measuring distance after position is reached.
 * @param hw is BubblesHardware object to manipulate
 * @return next state (HEAD_LEFT or MEASURE_DISTANCE)
 */
static inline TravelState_e _headLeft(BubblesHardware& hw);

/**
 * State HEAD_RIGHT function moves Bubbles head right for a predefined amount of
 * time. Switches to measuring distance after postion is reached.
 * @param hw is BubblesHardware object to manipulate
 * @return next state (HEAD_RIGHT or MEASURE_DISTANCE)
 */
static inline TravelState_e _headRight(BubblesHardware& hw);

/**
 * State HEAD_CENTER function moves Bubbles head to center. Switches to
 * measuring distance after position is reached.
 * @param hw is BubblesHardware object o manipulate
 * @return next state (HEAD_CENTER or MEASURE_DISTANCE)
 */
static inline TravelState_e _headCenter(BubblesHardware& hw);

/**
 * State MEASURE_DISTANCE function records the distance from Bubbles to some
 * object. Data is stored in the pointer address that must be specified before
 * this function call. Pointer is then compared with the three known Variables
 * to determine next state of operation.
 * @param hw is BubblesHardware object to manipulate
 * @return next state (HEAD_RIGHT, HEAD_CENTER, WHICH_WAY_SLCT, or ERROR)
 */
static inline TravelState_e _measureDistance(BubblesHardware& hw);

/**
 * State WHICH_WAY_SLCT function to handle the selection of which direction to
 * move Bubbles for the next several states. If the center distance is less than
 * the minimum turning radius then move backward. If left or right distance is
 * less than the minimum turning radius then move backward. Else turn left or
 * right dependign on which is greater.
 * @param hw is BubblesHardware obejct to manipulate
 * @return next state (MOVE_LEFT, MOVE_RIGHT, MOVE_BWD)
 */
static inline TravelState_e _whichWay(BubblesHardware& hw);

//==============================================================================
//                      Public Function Implementation
//==============================================================================

/**
 * Resets autonomous state-machine. Call once after a need to reset the state
 * machine such as moving from manual operation to autonomous.
 */
void auto_reset(void){
  _state = MOVE_FWD;
}

/**
 * Main loop function that will handle the current auton state. This functions
 * could take a large finite amount of time to run due to the nature of the
 * robot.
 * @param hw is BubblesHardware object to manipulate
 */
void auto_update(BubblesHardware& hw){
  // Run current state and update for next update call
  switch(_state){
    case MOVE_FWD:
      _state = _forward(hw);
      Serial.println(F("Forward"));
      break;
    case MOVE_BWD:
      _state = _backward(hw);
      Serial.println(F("Backward"));
      break;
    case MOVE_LEFT:
      _state = _left(hw);
      Serial.println(F("Left"));
      break;
    case MOVE_RIGHT:
      _state = _right(hw);
      Serial.println(F("Right"));
      break;
    case HEAD_LEFT:
      _state = _headLeft(hw);
      Serial.println(F("head left"));
      break;
    case HEAD_CENTER:
      _state = _headCenter(hw);
      Serial.println(F("head center"));
      break;
    case HEAD_RIGHT:
      _state = _headRight(hw);
      Serial.println(F("head right"));
      break;
    case MEASURE_DISTANCE:
      _state = _measureDistance(hw);
      Serial.println(F("Measure distance"));
      break;
    case WHICH_WAY_SLCT:
      _state = _whichWay(hw);
      Serial.println(F("Select direction"));
      break;
    case ERROR:
      hw.stopMoving();
      auto_reset(); // reset state-machine due to error
      Serial.println(F("Error"));
      break;
    default:
      hw.stopMoving();
      auto_reset(); //something broke, reset state-machine
      Serial.println(F("Default"));
      break;
  }
}

//==============================================================================
//                       Private Function Implementation
//==============================================================================

/**
 * State MOVE_FWD function move Bubbles forward until min distance is met.
 * then switches to turning head left
 * @param hw is BubblesHardware object to manipulate
 * @return next state (MOVE_FWD or HEAD_LEFT)
 */
static inline TravelState_e _forward(BubblesHardware& hw){
  TravelState_e retVal;
  long dist = hw.getUltrasonic().getDistance();
  Serial.print(F("Distance: "));
  Serial.println(dist);
  if(dist < STOPPING_DISTANCE){
    //stop the robot going to crash
    hw.stopMoving();
    //start scan for new direction
    retVal = HEAD_LEFT;
    _delayTimer = 0;
  }else{
    //move forward without a care in the world for this timestep
    hw.forward();
    retVal = MOVE_FWD;
  }
  return retVal;
}

/**
 * State MOVE_BWD function moves Bubbles backward for a predefined amount of
 * time. Switches to turning head left when time elapsed.
 * @param hw is BubblesHardware object to manipulate
 * @return next state (MOVE_BWD or HEAD_LEFT)
 */
static inline TravelState_e _backward(BubblesHardware& hw){
  TravelState_e retVal;
  if(_delayTimer >= BACKUP_TIME){
    //done backing up
    hw.stopMoving();
    retVal = HEAD_LEFT;
    _delayTimer = 0;
  }else{
    // continue backing up
    hw.backward();
    retVal = MOVE_BWD;
  }
  return retVal;
}

/**
 * State MOVE_LEFT function moves Bubbles left for a predefined amount of
 * time. Switches to moving forward when time elapsed.
 * @param hw is BubblesHardware object to manipulate
 * @return next state (MOVE_LEFT or MOVE_FWD)
 */
static inline TravelState_e _left(BubblesHardware& hw){
  TravelState_e retVal;
  if(_delayTimer >= MOVING_LEFT_TIME){
    //done turning left
    hw.stopMoving();
    retVal = MOVE_FWD;
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
 * @param hw is BubblesHardware object to manipulate
 * @return next state (MOVE_RIGHT or MOVE_FWD)
 */
static inline TravelState_e _right(BubblesHardware& hw){
  TravelState_e retVal;
  if(_delayTimer >= MOVING_RIGHT_TIME){
    //done turning right
    hw.stopMoving();
    retVal = MOVE_FWD;
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
 * @param hw is BubblesHardware object to manipulate
 * @return next state (HEAD_LEFT or MEASURE_DISTANCE)
 */
static inline TravelState_e _headLeft(BubblesHardware& hw){
  TravelState_e retVal;
  if(_delayTimer >= TURN_HEAD_LEFT_TIME){
    //done turning head left
    hw.stopMoving();
    _distanceVarPtr = &_leftDist;
    retVal = MEASURE_DISTANCE;
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
 * @param hw is BubblesHardware object to manipulate
 * @return next state (HEAD_RIGHT or MEASURE_DISTANCE)
 */
static inline TravelState_e _headRight(BubblesHardware& hw){
  TravelState_e retVal;
  if(_delayTimer >= TURN_HEAD_RIGHT_TIME){
    //done turning head right
    hw.stopMoving();
    _distanceVarPtr = &_rightDist;
    retVal = MEASURE_DISTANCE;
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
 * @param hw is BubblesHardware object o manipulate
 * @return next state (HEAD_CENTER or MEASURE_DISTANCE)
 */
static inline TravelState_e _headCenter(BubblesHardware& hw){
  TravelState_e retVal;
  if(_delayTimer >= TURN_HEAD_CENTER_TIME){
    //done turning head to center
    hw.stopMoving();
    _distanceVarPtr = &_centerDist;
    retVal = MEASURE_DISTANCE;
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
 * @param hw is BubblesHardware object to manipulate
 * @return next state (HEAD_RIGHT, HEAD_CENTER, WHICH_WAY_SLCT, or ERROR)
 */
static inline TravelState_e _measureDistance(BubblesHardware& hw){
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
 * @param hw is BubblesHardware obejct to manipulate
 * @return next state (MOVE_LEFT, MOVE_RIGHT, MOVE_BWD)
 */
static inline TravelState_e _whichWay(BubblesHardware& hw){
  TravelState_e retVal;
  if(_centerDist < MIN_TURN_RADIUS){
    retVal = MOVE_BWD;
  }else if(_leftDist < MIN_TURN_RADIUS && _rightDist < MIN_TURN_RADIUS){
    retVal = MOVE_BWD;
  }else if(_leftDist >= _rightDist){
    retVal = MOVE_LEFT;
  }else{
    retVal = MOVE_RIGHT;
  }
  _delayTimer = 0;
  return retVal;
}
