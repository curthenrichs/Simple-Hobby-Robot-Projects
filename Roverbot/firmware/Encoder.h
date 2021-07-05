/**
 * Encoder
 * @author Curt Henrichs
 * @date 7-22-2018
 *
 * Encoder is an abstraction of the optical wheel encoder used to track the
 * speed of Roverbot. The encoder is low-resoultion but should be sufficient
 * for bang-bang speed control.
 */
 
#ifndef ENCODER_H
#define ENCODER_H

//==============================================================================
//                                  Libraries
//==============================================================================

#include <Arduino.h>
#include <elapsedMillis.h>

//==============================================================================
//                            Class Declaration
//==============================================================================

/**
 * Encoder interfaces with custom optical encoder which uses a CDS cell to
 * determine light / dark on the wheel.
 */
class Encoder {

  private:
    byte analogPin;             //! Analog pin to read ADC raw value
    elapsedMillis updateTimer;  //! Timer used to determine speed
    uint32_t count;             //! Number of ticks captured
    bool encoderState;          //! whether light (true) / dark (false)
    float speed;                //! calculated current speed

  public:
    /**
     * Constructor create a default encoder (no hardware access)
     * @param pin is analog pin to attach encoder to
     */
    Encoder(byte pin);
    /**
     * Initialize hardware interface of encoder (at runtime). Used since
     * constuction happens before hardware 'enumerated'
     */
    void init(void);
    /**
     * Samples ticks of the encoder and determines speed on event. Call every
     * main event loop.
     */
    void update(void);
    /**
     * @return gets the current speed in rev / sec
     */
    float getSpeed(void);
};

#endif
