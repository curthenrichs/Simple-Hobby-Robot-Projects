
//this is the firmware for bubbles version 1.0
//it will contain the two command modes teleop and auton
//there will be a serial reader method and the haed controller
//releys will also be ported over and there will be a placeholder ultrasonic till the actual sensor is in place

//the head servo has a min position of 90 degrees and a max position of 140 degrees


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
// 9  
// 10 ultrasonic
// 11
// 12 robot direction
// 13

#include <Servo.h>
#include <SoftwareSerial.h>

///
///     external pin map varaibales
///
//controls the neck
Servo neck;
int neckPin = 3;
//the xbee serial device to pc  uses pins 2 and 8
SoftwareSerial xbee(2,8);
//relay control pins
//enable/disable body control
int enableDrivePin = 7;
//left turn pin
int leftPin = 6;
//right turn pin
int rightPin = 4;
//forward pin
int forwardPin = 5;
//toggle the motor's direction of fowrad pin
int motorDirTogglePin = 12;
//ultrasonic pin
int pingPin = 10;


///
///      internal signal varaibles
///
//holds the state of the bot
boolean auton = true;
//drivetrain engaged
boolean driveEngaged = true;
// the character for direction forward left or right
char driveMode = 'F';
//the value for the toggle motor pin
boolean toggleMotor = false;
//the value for if the neck should be up or down
boolean neckUp = false;
//the ultrasonic distance value
long distance = 0;


///
///    AI code varables     for more indepth explanations check out the roverbot code
///
//seelctor variable to determine when to turn left right or backwards
int whichway;
//holds the distance we check against to make sure we dont hit nothin
int thres1 = 55;
//not quite sure why this one is here but will get back to yall
int thres2 = 10;
//counts the number of times it takes a left turn
int AIcountL = 0;
//counts the number of times it takes a right turn
int AIcountR = 0;
//setinal variable for the backwards loop
int backSetinal = 0;
//counts the number of loops as a setinal to ge the robot to speed up
int turnCount = 0;






//-------------------------------------------------------------------------------< control code>-----------------------------------------------------------------

//initializes all code
void setup()
{
  //setup serial
  xbee.begin(9600);
  xbee.println("Started Serial Interface");
  
  //setup servos
  neck.attach(neckPin);
  
  //setup pins
  pinMode(enableDrivePin, OUTPUT);
  pinMode(leftPin, OUTPUT);
  pinMode(rightPin, OUTPUT);
  pinMode(forwardPin, OUTPUT);
  pinMode(motorDirTogglePin, OUTPUT);
  pinMode(pingPin, OUTPUT);
  
  digitalWrite(enableDrivePin, LOW);
  digitalWrite(leftPin, LOW);
  digitalWrite(rightPin, LOW);
  digitalWrite(forwardPin, LOW);
  digitalWrite(motorDirTogglePin, LOW);
  digitalWrite(pingPin, LOW);
}

//runs the state machine
void loop()
{
 //poll the ultrasonic sensor
 distance = ultrasonicSensor();
 
 //check serial comm
 //update state auton or teleop
 serialComm();
 
 //if in auton run the script else if in teleop update to teleop variables from serial comm update
 if(!auton) //teleop
 {
   //engage/disengage drivetrain from running
   if(driveEngaged)
     digitalWrite(enableDrivePin,HIGH);
   else
     digitalWrite(enableDrivePin,LOW);
     
   //toggle motor control
   if(toggleMotor)
     digitalWrite(motorDirTogglePin,HIGH);
   else
     digitalWrite(motorDirTogglePin,LOW);
     
   //direction setting
   if(driveMode == 'F')
   {
     digitalWrite(leftPin,LOW);
     digitalWrite(rightPin,LOW);
     digitalWrite(forwardPin,HIGH);
   }
   else if(driveMode == 'R')
   {
     digitalWrite(leftPin,LOW);
     digitalWrite(forwardPin,LOW);
     digitalWrite(rightPin,HIGH);
   }
   else
   {
     digitalWrite(rightPin,LOW);
     digitalWrite(forwardPin,LOW);
     digitalWrite(leftPin,HIGH);
   }
   
   //neck control
   if(neckUp)
   {
     neck.write(140);
   }
   else
   {
     neck.write(90);
   }
   
   delay(200);
 }
 else //auton
 {
   //engage drivetrain
   digitalWrite(enableDrivePin,HIGH);
   //set the direction for forward on motor to go forward
   digitalWrite(motorDirTogglePin,HIGH);
   
   //set head to low position
   neck.write(90);
   
   //start running script
   if(distance > thres1)
   {
      AIcountL = 0;
      AIcountR = 0;
     
     //drive forward 
     digitalWrite(leftPin,LOW);
     digitalWrite(rightPin,LOW);
     digitalWrite(forwardPin,HIGH);
     delay(200);
   }
   else
   {
      //stop driving
      digitalWrite(leftPin,LOW);
      digitalWrite(rightPin,LOW);
      digitalWrite(forwardPin,LOW);
      delay(100);
      
      //implement the if too close back up first
      if(distance < 10)
      {
        //sets the motor forward to the reverse of robot forward so forward = backwards
        digitalWrite(motorDirTogglePin,LOW);
        digitalWrite(leftPin,LOW);
        digitalWrite(rightPin,LOW);
        digitalWrite(forwardPin,HIGH);
        delay(500);
        
        //stop driving
        digitalWrite(leftPin,LOW);
        digitalWrite(rightPin,LOW);
        digitalWrite(forwardPin,LOW);
        delay(100);
      }
      
      //gets which direction has mpst distance to travel
      whichway = leftandright();
      
      //if right
      if(whichway == 0)
      {
        while(turnCount < 2)
        {
          digitalWrite(leftPin,LOW);
          digitalWrite(rightPin,HIGH);
          digitalWrite(forwardPin,LOW);
          delay(200);
          turnCount++;
        }
        
        turnCount = 0;
      }
      else if(whichway == 1)
      {
        while(turnCount < 2)
        {
          digitalWrite(leftPin,HIGH);
          digitalWrite(rightPin,LOW);
          digitalWrite(forwardPin,LOW);
          delay(200);
          turnCount++;
        }
        
        turnCount = 0;
      }
      else
      {
        while (backSetinal == 0)
        {
           //sets the motor forward to the reverse of robot forward so forward = backwards
           digitalWrite(motorDirTogglePin,LOW);
           digitalWrite(leftPin,LOW);
           digitalWrite(rightPin,LOW);
           digitalWrite(forwardPin,HIGH);
           delay(500);
           
           backSetinal++;
        }
        
        //stop driving
        digitalWrite(leftPin,LOW);
        digitalWrite(rightPin,LOW);
        digitalWrite(forwardPin,LOW);
        delay(100);
        
        backSetinal = 0;
      }
   }
 }
}

//---------------------------------------------------------------<AI METHODS>--------------------------------------------------------------------------------------------
int leftandright()
{
  long leftDist,rightDist;
  
  //turns head left and calls value from ultrasonic
  digitalWrite(leftPin,HIGH);
  digitalWrite(rightPin,LOW);
  digitalWrite(forwardPin,LOW);
  delay(200);
  //stop
  digitalWrite(leftPin,LOW);
  digitalWrite(rightPin,LOW);
  digitalWrite(forwardPin,LOW);
  delay(200);
  
  //get ultrasonic value
  leftDist =  ultrasonicSensor();
  
  //turns head right and does the same thing
  digitalWrite(leftPin,LOW);
  digitalWrite(rightPin,HIGH);
  digitalWrite(forwardPin,LOW);
  delay(200);
  //stop
  digitalWrite(leftPin,LOW);
  digitalWrite(rightPin,LOW);
  digitalWrite(forwardPin,LOW);
  delay(200);
  
  //get ultrasonic value
  rightDist =  ultrasonicSensor();
  
  //now determine the course of action
  if(AIcountL > 5 || AIcountR > 5)
  {
    whichway = 2; 
    
    AIcountL = 0;
    AIcountR = 0;
  }
  else
  {
    //favors turning right
    if(leftDist <= rightDist)
    {
      AIcountR++;
      whichway = 0;
    } 
    else //favors turning left
    {
      AIcountL++;
      whichway = 1;
    }
  }
  return whichway;
}



//----------------------------------------------------------------<UTILTIY METHODS>----------------------------------------------------------------------------------------
//Function: serialComm()
//Purpose: implements all of the serial communication logic

void serialComm()
{
  //input placeholder
  String in = "";
  
  //if there is something in the buffer
  if(xbee.available())
  {
    char temp = ';';
    do
    {
      temp = xbee.read();
      in += temp; 
    }
    while(temp != ';');
  }
  
  //decode into values
  //set the enabe auton  if E enable auton if D disable auto
  if(in.charAt(0) == 'E')
  {
    auton = true;
  }
  else //D
  {
    auton = false;
  }
  //set if the drivetrain should be active or not E or D
  if(in.charAt(1) == 'E')
  {
    driveEngaged = true;
  }
  else //D
  {
    driveEngaged = false;
  }
  //gets the direction of the drivetrain travel F,L,R
  driveMode = in.charAt(2);
  //whether to toggle the motor backwards or not  F or B
  if(in.charAt(3) == 'F')
  {
    toggleMotor = false; 
  }
  else // B
  {
    toggleMotor = true;
  }
  //determien the state of the neck
  if(in.charAt(4) == 'U')
  {
    neckUp = true;
  }
  else //D
  {
    neckUp = false;
  }
  //output the ultrasonic
  String out = String(distance) + ";";
  xbee.print(out);
}

//Function: ultrasonicSensor()
//Purpose: implemenets all of the distnce calculation and accusition stuff of the ultrasonic sensor

long ultrasonicSensor()
{
   //these are the variabels for the duration of the high pulse and the distance away an object is
  long duration, inches;
 
  //trigger the ping with a two mircosecond high pulse then drop lw before switching to input
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  
  //switch to input then wait for the trigger
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  
  //convert to inches
  inches = duration/74/2;
  
  //give system time to reset values
  delay(100);
  
  //return the value to the program
  return inches;
}


