/*
 * File RelayBoard.h
 * Author Curt Henrichs
 * Date 3/7/2015
 * Purpose This is the desrciption of the RelayBoard class which controls the action of the seeedstudio
 * relay shield. The behavior is high level in that we can command directions and the class chooses what to
 * do with that information.
 */

#ifndef RELAY_H
#define RELAY_H

#include "Arduino.h"

class RelayBoard
{
	private:
		int disableRelayPin;
		int leftMovePin;
		int rightMovePin;
		int linearMovePin;
	public:
		RelayBoard(int disableRelayPin,int linearMovePin,int leftMovePin, int rightMovePin);
		~RelayBoard();
		void linearMove();
		void leftMove();
		void rightMove();
		void toggleDisable(bool disable);
		void stop();
};

#endif
