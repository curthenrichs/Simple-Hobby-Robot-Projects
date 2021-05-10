//testing the realys for bubbles to see why stuff is not working

//current hypotheisis is that the forward pin is not responding going to first heck wia driving left

#include <SoftwareSerial.h>

//enable/disable body control
int enableDrivePin = 7;
//left turn pin
int leftPin = 6;
//right turn pin
int rightPin = 4;
//forward pin
int forwardPin = 5;

//the xbee serial device to pc  uses pins 2 and 8
//SoftwareSerial xbee(2,8);

void setup()
{
 // xbee.begin(9600);
 
  pinMode(enableDrivePin, OUTPUT);
  pinMode(leftPin, OUTPUT);
  pinMode(rightPin, OUTPUT);
  pinMode(forwardPin, OUTPUT);
  
  digitalWrite(enableDrivePin, HIGH);
  digitalWrite(leftPin, LOW);
  digitalWrite(rightPin, LOW);
  digitalWrite(forwardPin, LOW);
}

void loop()
{
  //set enable pin to active
  //digitalWrite(enableDrivePin,HIGH);
   
  //drive forward
  //digitalWrite(leftPin,HIGH); 
   //digitalWrite(rightPin,HIGH);
   digitalWrite(forwardPin,HIGH); 
  
  //delay time
  delay(1000*15);
  
  digitalWrite(forwardPin,LOW);
  
  delay(100);
}

//wont work if just hold the relay high/ must switch every once and awhile to make it work
