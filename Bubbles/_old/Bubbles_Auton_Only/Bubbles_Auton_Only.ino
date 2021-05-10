#include <Servo.h>
#include <SoftwareSerial.h>
#include "RelayBoard.h"
#include "UltrasonicSensor.h"
#include "EyeLED.h"
#include "MotorController.h"

//this piece of code is tha low level autonomous code for bubbles
//releys will also be ported over and there will be a placeholder ultrasonic till the actual sensor is in place
//the head servo has a min position of 90 degrees and a max position of 140 degrees

//Currently the project is refactored and should be more easy to reaad and comprehend

//note: changed the ultrasonic to pin 13, stop pin to A0, and RBG to 9,10,11 respectivly. 

// pins used
// 0  rx
// 1  tx
// 2  xbee
// 3  neck (pwm)
// 4  relay
// 5  relay
// 6  relay
// 7  relay
// 8  xbee
// 9  red LED
// 10 green LED
// 11 blue LED
// 12 robot direction
// 13 ultrasonic pin
// A0 stop pin

//================================================================
//                       PINS and Devices
//================================================================

//controls the neck
Servo neck;
int neckPin = 3;

//the xbee serial device to pc  uses pins 2 and 8
SoftwareSerial xbee(2,8);

//relay control pins
RelayBoard relayBoard(7,5,6,4);

//ultrasonic Sensor
UltrasonicSensor ultrasonic(13);

//Eye LEDS 
EyeLED leds(9,11,10);

//Custom Motor Controller
MotorController motorController(12,A0);

/*
 * method initializes all pins
 */
void setup(){
	//setup serial
	xbee.begin(9600);
	xbee.println("Started Serial Interface");
	
	//setup servos
	neck.attach(neckPin);

        //give time for bubbles to be ready to move
        delay(1000);
}

//================================================================
//                   Interrupt Serivce Routine
//================================================================

/*
 * Handles the perriodic interrupt for the timer2. This interrupt
 * is inchanrge of pulsing any on relays on the RelayBoard
 */


//================================================================
//                         Main Code
//================================================================

//holds the state of the bot
boolean autonState = true;
//drivetrain engaged
boolean driveEngaged = true;
// the character for direction forward left or right
char driveMode = 'F';
//the value for the toggle motor pin
boolean toggleMotor = false;
//the value for if the neck should be up or down
boolean neckUp = false;

/*
 * Method loops infintely for the auton code
 */
void loop(){     
	//poll the ultrasonic sensor
	long distance = ultrasonic.getDistance();
	
	//engage drivetrain
	disableOnboardControl(false);
	
	//set head to low position
	//neck.write(90);

        //Set the LEDs to a vlaue
        //leds.red();
	
	//call auton
	auton(distance);
}

//==============================================================
//                    Auton Variables and Methods
//==============================================================
//counts the number of times it takes a left turn
int AIcountL = 0;
//counts the number of times it takes a right turn
int AIcountR = 0;
//setinal variable for the backwards loop
int backSetinal = 0;
//counts the number of loops as a setinal to ge the robot to speed up
int turnCount = 0;

/*
 * Runs the auton script which is a basic wall banger based off of the rover-bot code
 */
void auton(long distance){
	//if we are not going to hit anything
	if(distance > 40){
		//reset counters
		AIcountL = 0;
		AIcountR = 0;
		
		//drive forward
		forward();
		
		//delay for robot to move in real world
		delay(500);
	} 
        //if we are going to crash
        else { 
		//stop driving
		stopMoving();
		
		//give time to react
		delay(100);
		
		//if too close back up first
		if(distance < 10){
			reverse();
                        
                        //delay for full action which takes 15 seconds
			delay(1000 * 15);
			
			//stop driving
			stopMoving();
			delay(100);
		}
		
		//gets which direction has most distance to travel
		int whichway = determineDirectionToTravel();
		
		//if right
		if(whichway == 0){
			forwardRight();
			delay(1000 * 15);
		} else if(whichway == 1){ //left
			forwardLeft();
			delay(1000 * 15);
		} else { //we need to backup
			//sets the motor forward to the reverse of robot forward so forward = backwards
			reverse();
			delay(1000 * 15);
			
			//stop driving
			stopMoving();
			delay(100);
		}
	}
}

/*
 * Determines if the robot should turn right or left based on the distances it collects
 * or determines if it is in a corner and thus needs to back up out of the corner first
 */
int determineDirectionToTravel(){
	//holds the distances calculated by the ultrasonic sensor
	long leftDist,rightDist;
	//selected direction 0,1,2 right,left,reverse
	int whichway = 2;
	
	//move head around collecting the values
	moveHead(leftDist,rightDist);
	
	//if we are stuck in a corner and/or add some psuedo randomness to behavior
	//then we want to back up
	if(AIcountL > 5 || AIcountR > 5){
		whichway = 2;
	
		AIcountL = 0;
		AIcountR = 0;
	} else { //else we check to see if we want to turn left or right
		//favors turning right
		if(leftDist <= rightDist){
			AIcountR++;
			whichway = 0;
		} else { //favors turning left
			AIcountL++;
			whichway = 1;
		}
	}
	return whichway;
}

/*
 * Moves the head left then right and then back to center collecting
 * left and right distances
 */
void moveHead(long &leftDist, long &rightDist){
	//turns head left and calls value from ultrasonic
	turnLeftOnly();
	delay(1000 * 15);
	stopMoving();
	delay(100);
	leftDist =  ultrasonic.getDistance();
	
	//turns head right and does the same thing
	turnRightOnly();
	delay(1000 * 15);
	stopMoving();
	delay(100);
	rightDist =  ultrasonic.getDistance();
	
	//return to center position
	centerHead();
        delay(1000 * 15);
}

//=============================================================================
//                            Utility Methods
//==============================================================================
/*
 * Commands the robot to go forwards
 */
void forward(){
	motorController.forward();
	relayBoard.linearMove();
}

/*
 * Commands the robot to go backwards
 */
void reverse(){
	motorController.reverse();
	relayBoard.linearMove();
}

/*
 * Sets the direction of the motor to forward and turn left
 */
void forwardLeft(){
	motorController.forward();
	relayBoard.leftMove();
}

/*
 * Sets the direction of the motor to forward and turn right
 */
void forwardRight(){
	motorController.forward();
	relayBoard.rightMove();
}

/*
 * Sets the direction of the motor to backwards and turns right
 */
void backwardRight(){
	motorController.reverse();
	relayBoard.rightMove();
}

/*
 * Sets the direction of the motor to backwards and turns left
 */
void backwardLeft(){
	motorController.reverse();
	relayBoard.leftMove();
}

/*
 * Disables the drive motor and turns the robot
 */
void turnRightOnly(){
	motorController.stop();
	relayBoard.rightMove();
}

/*
 * Disables the drive motor and turns the robot
 */
void turnLeftOnly(){
	motorController.stop();
	relayBoard.leftMove();
}

/*
 * Disables the drive motor and turns the robot to center
 */
void centerHead(){
	motorController.stop();
	relayBoard.linearMove();
}

/*
 * Stops the robot where it is will not move until motorStop pin is low
 */
void stopMoving(){
	motorController.stop();
	relayBoard.stop();
}

/*
 * Disables the onboard processor from commanding bubbles this resets the configuration 
 * on the motor controller pins as well as turning on/off the relay signaling that bubbles
 * can do its own thing.
 */
void disableOnboardControl(boolean disable){
	motorController.forward();
	relayBoard.toggleDisable(disable);
}
