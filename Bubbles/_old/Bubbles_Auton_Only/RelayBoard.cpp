/*
 * File RelayBoard.cpp
 * Author Curt Henrichs
 * Date 3/7/2015
 * Purpose This is the implmentation of the RelayBoard class which controls the action of the seeedstudio
 * relay shield. The behavior is high level in that we can command directions and the class chooses what to
 * do with that information.
 */

#include "Arduino.h"
#include "RelayBoard.h"

/*
 * RelayBoard Constructor
 */
RelayBoard::RelayBoard(int disablePin,int linearPin,int leftPin, int rightPin)
{
	//set to private fields
	disableRelayPin = disablePin;
	linearMovePin = linearPin;
	leftMovePin = leftPin;
	rightMovePin = rightPin;
	
	//set the pinModes
	pinMode(disableRelayPin, OUTPUT);
	pinMode(leftMovePin, OUTPUT);
	pinMode(rightMovePin, OUTPUT);
	pinMode(linearMovePin, OUTPUT);
	
	//set to default values
	digitalWrite(disableRelayPin, LOW);
	digitalWrite(leftMovePin, LOW);
	digitalWrite(rightMovePin, LOW);
	digitalWrite(linearMovePin, LOW);
}

/*
 * RelayBoard Destructor
 */
RelayBoard::~RelayBoard()
{
	/*nothing to destruct*/
}

/*
 * put board in move linear state
 */
void RelayBoard::linearMove()
{
	digitalWrite(leftMovePin,LOW);
	digitalWrite(rightMovePin,LOW);
	digitalWrite(linearMovePin,HIGH);
}

/*
 * put board in move left state
 */
void RelayBoard::leftMove()
{
	digitalWrite(leftMovePin,HIGH);
	digitalWrite(rightMovePin,LOW);
	digitalWrite(linearMovePin,LOW);
}

/*
 * put board in move right state
 */
void RelayBoard::rightMove()
{
	digitalWrite(leftMovePin,LOW);
	digitalWrite(rightMovePin,HIGH);
	digitalWrite(linearMovePin,LOW);
}

/*
 * put board in disable state
 */
void RelayBoard::toggleDisable(bool disable)
{
	if(disable)
	{
		digitalWrite(disableRelayPin,LOW);
	}
	else
	{
		digitalWrite(disableRelayPin,HIGH);
	}
}

/*
 * put board in stop state
 */
void RelayBoard::stop()
{
	digitalWrite(leftMovePin,LOW);
	digitalWrite(rightMovePin,LOW);
	digitalWrite(linearMovePin,LOW);
}
