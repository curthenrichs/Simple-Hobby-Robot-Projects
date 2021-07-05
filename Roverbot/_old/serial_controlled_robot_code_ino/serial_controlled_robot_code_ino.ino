#include <Servo.h>;

const int strservPin = 5;

String oldinfo = "";
String info = "";
int steerpos = 85;
int motorspeed = 0;
int motordi = 0;
int lnum = 0;

Servo steerServo;

void setup()
{
  // start serial port at 9600 bps:
  Serial.begin(9600);
  Serial.println("i have activated this port");
  steerServo.attach(strservPin);
  steerServo.write(85);
}

void loop(){
  if (Serial.available()){
    char mychar = (char)Serial.read();
    info += mychar;
    Serial.println(info);
  }
  Serial.println("loop number...");
  Serial.println(lnum);
  lnum = lnum + 1;
  
  
    if (info == "l"){
        steerpos = 110;
    } else if (info == "r"){
        steerpos = 70;
    } else if (info == "c"){
        steerpos = 85;
    } else if (info == "R"){
        motordi = 1;
    } else if (info == "F"){
        motordi = 0;
    } else if (info == "0"){
        motorspeed = 0;
    } else if (info == "1"){
        motorspeed  = 140;
    } else if(info == "2"){
        motorspeed = 160;
    } else if(info == "3"){
        motorspeed = 180;
    } else if(info == "4"){
        motorspeed = 200;
    } else if(info == "5"){
        motorspeed = 220;
    } else if (info == "6"){
        motorspeed  = 240;
    } else if (info == "7"){
        motorspeed = 250;
    }
  
  
  steerServo.write(steerpos);
  
  if(motordi == 0){
    digitalWrite(12,LOW);
  } else {
    digitalWrite(12,HIGH);
  }
  digitalWrite(9,LOW);
  analogWrite(3,motorspeed);
  
  
  delay(1000);
  info = "";
 
  
 
}
  
  



