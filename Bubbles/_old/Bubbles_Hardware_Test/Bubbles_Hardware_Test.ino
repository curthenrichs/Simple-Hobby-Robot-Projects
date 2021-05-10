#include <Servo.h>
#include <SoftwareSerial.h>
#include "RelayBoard.h"
#include "UltrasonicSensor.h"
#include "EyeLED.h"
#include "MotorController.h"

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

//controls the neck
Servo neck;
int neckPin = 3;

//the xbee serial device to pc  uses pins 2 and 8
//SoftwareSerial xbee(2,8);

//relay control pins
//RelayBoard relayBoard(7,5,6,4);

//ultrasonic Sensor
UltrasonicSensor ultrasonic(13);

//Eye LEDS 
//EyeLED leds(9,11,10);

//Custom Motor Controller
MotorController motorController(12,A0);

void setup(){
         Serial.begin(9600); 
}

void loop(){
          //long inches = ultrasonic.getDistance();
          //Serial.println(inches);
          
           //Motor test
          motorController.forward();
          //motorController.stop();
          
          delay(100);
}


