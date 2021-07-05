/**
 * firmware
 * @author Curt Henrchs
 * @date 7-22-2018
 *
 * Firmware for Roverbot, which is a small (approximatly 1 foot in length) with
 * a single drive motor and a steering servo. The sensor suite is limited to
 * an ultrasonic mounted on a servo at approximatly half a foot off the ground
 * and a simplistic homemade optical encoder used to sense general speed
 * information.
 */

//==============================================================================
//                               Libraries
//==============================================================================

#include "HardwareConfig.h"
#include "Hardware.h"
#include "Autonomous.h"

//==============================================================================
//                            Private Members
//==============================================================================

static Hardware _roverHardware;         //! Roverbot

//==============================================================================
//                                MAIN
//==============================================================================

void setup(void) {
  _roverHardware.begin();
  auto_reset();
}

void loop(void) {
  _roverHardware.update();
  auto_update(_roverHardware);
  delay(1);
}
