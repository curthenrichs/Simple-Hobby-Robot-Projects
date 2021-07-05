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
 
#ifndef AUTONOMOUS_H
#define AUTONOMOUS_H

//==============================================================================
//                                  Libraries
//==============================================================================

#include <Arduino.h>
#include "Hardware.h"

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
void auto_update(Hardware& hw);

#endif
