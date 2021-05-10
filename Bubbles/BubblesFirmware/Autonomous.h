/**
 * Autonomous
 * @author Curt Henrichs
 * @date 6-24-17
 *
 * Autonomous control of Bubbles uses a "wall-banger" random wandering
 * algorithm to go to no place in particular. The code runs as a main-loop
 * state machien as is dependent on having update called regularly. 
 */

#ifndef AUTONOMOUS_H
#define AUTONOMOUS_H

//==============================================================================
//                                  Libraries
//==============================================================================

#include <Arduino.h>
#include "BubblesHardware.h"

//==============================================================================
//                         Public Function Prototypes
//==============================================================================

/**
 * Resets autonomous state-machine. Call once after a need to reset the state
 * machine such as moving from manual operation to autonomous.
 */
void auto_reset(void);

/**
 * Main loop function that will handle the current auton state. This functions
 * could take a large finite amount of time to run due to the nature of the
 * robot.
 * @param hw is BubblesHardware object to manipulate
 */
void auto_update(BubblesHardware& hw);

#endif
