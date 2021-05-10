/**
 * RelayBoard
 * @author Curt Henrichs
 * @date 6-24-17
 *
 * This is the desrciption of the RelayBoard class which controls the
 * action of the seeedstudio relay shield. The behavior is high level in that
 * can command directions for the physical Bubbles robot.
 */

//==============================================================================
//                               Libraries
//==============================================================================

#include "RelayBoard.h"

//==============================================================================
//                       Constant and Macro Definition
//==============================================================================

#define POWER_CYCLE_TIME 12000

//==============================================================================
//                            Class Implementation
//==============================================================================

/**
 * Constructor for relay board takes the physical pin layout and maps to
 * software structure.
 * @param disablePin pin connected to disbale connection relay.
 * @param forwardPin pin connected to head forward relay
 * @param leftPin pin connected to head left relay
 * @param rightPin pin connected to head right relay
 */
RelayBoard::RelayBoard(byte disablePin, byte forwardPin, byte leftPin, byte rightPin){

	// set members
	_disablePin = disablePin;
	_leftPin = leftPin;
	_rightPin = rightPin;
	_forwardPin = forwardPin;

	//set the pinModes
	pinMode(_disablePin, OUTPUT);
	pinMode(_leftPin, OUTPUT);
	pinMode(_rightPin, OUTPUT);
	pinMode(_forwardPin, OUTPUT);

	//set to default values
	digitalWrite(_disablePin, LOW);
	digitalWrite(_leftPin, LOW);
	digitalWrite(_rightPin, LOW);
	digitalWrite(_forwardPin, LOW);

 //clear timer
 _timer = 0;
}

/**
 * Commands Bubbles to head forward
 */
void RelayBoard::forward(void){
	digitalWrite(_leftPin,LOW);
	digitalWrite(_rightPin,LOW);
	digitalWrite(_forwardPin,HIGH);
 
}

/**
 * Commands Bubbles to head left
 */
void RelayBoard::left(void){
	digitalWrite(_leftPin,HIGH);
	digitalWrite(_rightPin,LOW);
	digitalWrite(_forwardPin,LOW);
}

/**
 * Commands Bubbles to head right
 */
void RelayBoard::right(void){
	digitalWrite(_leftPin,LOW);
	digitalWrite(_rightPin,HIGH);
	digitalWrite(_forwardPin,LOW);
}

/**
 * Disables the left, right, and forward relays
 */
void RelayBoard::stop(void){
	digitalWrite(_leftPin,LOW);
	digitalWrite(_rightPin,LOW);
	digitalWrite(_forwardPin,LOW);
}

/**
 * Sets the enable/disable state of the relay. If disabled then Bubbles
 * original hardware behavior takes over. When enabled this controlelr is
 * commanding Bubbles.
 */
void RelayBoard::disable(bool dis){
	digitalWrite(_disablePin,!dis);
}

/**
 * periodic control function to cycle power to bubbles relays for 
 * continous control.
 */
void RelayBoard::update(void){
  if(_timer >= POWER_CYCLE_TIME){
    _timer -= POWER_CYCLE_TIME;
    bool d = false, l = false, r = false, f = false;

    //clear relays
    if(digitalRead(_disablePin)){
      digitalWrite(_disablePin,LOW);
      d = true;
    }
    if(digitalRead(_leftPin)){
      digitalWrite(_leftPin,LOW);
      l = true;
    }
    if(digitalRead(_rightPin)){
      digitalWrite(_rightPin,LOW);
      r = true;
    }
    if(digitalRead(_forwardPin)){
      digitalWrite(_forwardPin,LOW);
      f = true;
    }

    //Re-enable active relays
    if(d || l || r || f){
      delay(100);
      if(d){
        digitalWrite(_disablePin,HIGH);
        Serial.println(F("Disable Pin"));
      }
      if(l){
        digitalWrite(_leftPin,HIGH);
        Serial.println(F("Left pin"));
      }
      if(r){
        digitalWrite(_rightPin,HIGH);
        Serial.println(F("Right Pin"));
      }
      if(f){
        digitalWrite(_forwardPin,HIGH);
        Serial.println(F("Forward Pin"));
      }
    }
  }
}

