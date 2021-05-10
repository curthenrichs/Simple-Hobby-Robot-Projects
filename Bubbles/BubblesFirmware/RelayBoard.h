/**
 * RelayBoard
 * @author Curt Henrichs
 * @date 6-24-17
 *
 * This is the desrciption of the RelayBoard class which controls the
 * action of the seeedstudio relay shield. The behavior is high level in that
 * can command directions for the physical Bubbles robot.
 */

#ifndef RELAYBOARD_H
#define RELAYBOARD_H

//==============================================================================
//                               Libraries
//==============================================================================

#include <Arduino.h>
#include <elapsedMillis.h>

//==============================================================================
//                            Class Declaration
//==============================================================================

/**
 * Implements the abstract control layer from physical relay board to Bubbles
 * hardware control logic.
 */
class RelayBoard{
	private:
		// Pin for disabling the control connection
		byte _disablePin;
		// pin for commanding Bubble to turn left
		byte _leftPin;
		// pin for commanding Bubbles to turn right
		byte _rightPin;
		// pin for commanding Bubble to move head forward
		byte _forwardPin;
   //periodic timer for power cycling relay pins
   elapsedMillis _timer;

	public:
		/**
		 * Constructor for relay board takes the physical pin layout and maps to
		 * software structure.
		 * @param disablePin pin connected to disbale connection relay.
		 * @param forwardPin pin connected to head forward relay
		 * @param leftPin pin connected to head left relay
		 * @param rightPin pin connected to head right relay
		 */
		RelayBoard(byte disablePin, byte forwardPin,byte leftPin, byte rightPin);
		/**
		 * Commands Bubbles to head forward
		 */
		void forward(void);
		/**
		 * Commands Bubbles to head left
		 */
		void left(void);
		/**
		 * Commands Bubbles to head right
		 */
		void right(void);
		/**
		 * Disables the left, right, and forward relays
		 */
		void stop(void);
		/**
		 * Sets the enable/disable state of the relay. If disabled then Bubbles
		 * original hardware behavior takes over. When enabled this controlelr is
		 * commanding Bubbles.
		 */
		void disable(bool dis);
   /**
    * periodic control function to cycle power to bubbles relays for 
    * continous control.
    */
   void update(void);
};

#endif
