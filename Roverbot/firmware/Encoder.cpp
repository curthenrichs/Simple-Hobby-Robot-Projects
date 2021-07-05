/**
 * Encoder
 * @author Curt Henrichs
 * @date 7-22-2018
 *
 * Encoder is an abstraction of the optical wheel encoder used to track the
 * speed of Roverbot. The encoder is low-resoultion but should be sufficient
 * for bang-bang speed control.
 */

//==============================================================================
//                               Libraries
//==============================================================================

#include "Encoder.h"

//==============================================================================
//                         Constant and Macro Definition
//==============================================================================

#define UPDATE_TIME               150 //! Calculate new speed interval

#define ANALOG_ENCODER_THRESHOLD  350 //! Light value mapping (from experiment)

#define TICKS_PER_REV             4.0 //! Encoder conversion

//==============================================================================
//                            Class Implementation
//==============================================================================

/**
 * Constructor create a default encoder (no hardware access)
 * @param pin is analog pin to attach encoder to
 */
Encoder::Encoder(byte pin) {
  analogPin = pin;
  updateTimer = 0;
  speed = 0;
  count = 0;
}

/**
 * Initialize hardware interface of encoder (at runtime). Used since
 * constuction happens before hardware 'enumerated'
 */
void Encoder::init(void) {
  encoderState = analogRead(analogPin) > ANALOG_ENCODER_THRESHOLD;
}

/**
 * Samples ticks of the encoder and determines speed on event. Call every
 * main event loop.
 */
void Encoder::update(void) {

  bool nextState = analogRead(analogPin) > ANALOG_ENCODER_THRESHOLD;
  if (nextState != encoderState) {
    encoderState = nextState;
    count++; //tick
  }

  if (updateTimer >= UPDATE_TIME) {
    updateTimer -= UPDATE_TIME;
    speed = (count / (UPDATE_TIME /  1000.0)) / TICKS_PER_REV;
    count = 0;
  }
}

/**
 * @return gets the current speed in rev / sec
 */
float Encoder::getSpeed(void) {
  return speed;
}
