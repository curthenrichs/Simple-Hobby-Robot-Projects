#include <Servo.h>

//ultrasonic constants
#define ULTRASONIC_MIN_DISTANCE            30  //inches
#define BACKUP_DISTANCE                    15  //inches

//Steering Servo constants
#define STEER_SERVO_CENTER                 85  //degrees
#define STEER_SERVO_LEFT                   110 //degrees
#define STEER_SERV0_RIGHT                  70  //degrees

//Head Servo constants
#define HEAD_SERVO_CENTER                  85  //degrees
#define HEAD_SERVO_LEFT                    60  //degrees
#define HEAD_SERVO_RIGHT                   125 //degrees

//Hardware pin constants
#define ULTRASONIC_PIN                     7
#define STEER_SERVO_PIN                    5
#define HEAD_SERVO_PIN                     6
#define MOTOR_CONTROLLER_BRAKE_PIN         9
#define MOTOR_CONTROLLER_DIRECTION_PIN     12
#define MOTOR_CONTROLLER_PWM_PIN           3
#define ACC_X_PIN                          A3
#define ACC_Y_PIN                          A4

//Enumeration of direction operations
enum directionOptions{
  TURN_LEFT,
  TURN_RIGHT,
  BACKUP
};

//accelermeter constants
#define ACCEPTABLE_ACCELERATION            1 //ft/s^2
#define STUCK_THRESHOLD                    3 //loops with low acceleration at start of forward

//servo motors
Servo steerServo;
Servo headServo;

//accelerometer readings
volatile double y_base = 0;

void setup(){
  //debugging serial
  Serial.begin(9600);
  
  //Servo motor setup
  steerServo.attach(STEER_SERVO_PIN);
  headServo.attach(HEAD_SERVO_PIN);
  steerServo.write(STEER_SERVO_CENTER);
  headServo.write(HEAD_SERVO_CENTER);

  delay(1);

  //acc initial values
  y_base = getAcc_sigFigs();
}
//------------------------------------------------------[main]-------------------------------------------------------------------------
long distance;
int whichway;
int backupCount = 0;
int accCount = 0;
int possibleStuckCount = 0;

void loop(){

  //Run robot code
  distance = ultrasonicSensor();
  if (distance > ULTRASONIC_MIN_DISTANCE && possibleStuckCount < STUCK_THRESHOLD){
    //if we should be accelerating then check acceleration
    int speedOffset = 0;
    if(accCount < 4){
      accCount++;
      double acc = getAcc_sigFigs();
      if(acc < ACCEPTABLE_ACCELERATION){
         speedOffset = 40;
         possibleStuckCount++;
      }
    }

    //set to move forward one time-step
    steerServo.write(STEER_SERVO_CENTER);
    forward(160 + speedOffset); 
    
  }else{

    //stop robot and reset to expect acceleration when driving
    accCount = 0;
    stopMove();
    y_base = getAcc_sigFigs();
    
    //determine if too close to object tmust backup first
    distance = ultrasonicSensor();
    if(distance < BACKUP_DISTANCE || possibleStuckCount == STUCK_THRESHOLD){
      possibleStuckCount = 0;
      backupCount = 0;
      steerServo.write(STEER_SERVO_CENTER);
      while(backupCount < 5){
        backwards(235);
        backupCount++;
        delay(150);
      }
      stopMove();
    }
    
    //determine which way to turn
    whichway = determineDirection();
    if (whichway == TURN_LEFT){
      //turn left
      steerServo.write(STEER_SERVO_LEFT);
      forward(200);
      delay(500);
    }else if (whichway == TURN_RIGHT){
      //turn right
      steerServo.write(STEER_SERV0_RIGHT);
      forward(200);
      delay(500);
    }else{
      //backup since in a corner
      backupCount = 0;
      steerServo.write(STEER_SERVO_CENTER);
      while(backupCount < 5){
        backwards(235);
        backupCount++;
        delay(150);
      }
      stopMove();
    }
  }
  
  delay(500);
}

//-----------------------------------------------[Motor Controller]----------------------------------------------------------------
void forward(int pwmSpeed){
  digitalWrite(MOTOR_CONTROLLER_DIRECTION_PIN,LOW);
  digitalWrite(MOTOR_CONTROLLER_BRAKE_PIN,LOW);
  analogWrite(MOTOR_CONTROLLER_PWM_PIN,pwmSpeed);
}

void backwards(int pwmSpeed){
  digitalWrite(MOTOR_CONTROLLER_DIRECTION_PIN,HIGH);
  digitalWrite(MOTOR_CONTROLLER_BRAKE_PIN,LOW);
  analogWrite(MOTOR_CONTROLLER_PWM_PIN,pwmSpeed);
}

void stopMove(){
  analogWrite(MOTOR_CONTROLLER_PWM_PIN,0); //outputs a PWM of 0%
  delay(250);
}


//----------------------------------------------[which way to move]----------------------------------------------------------------
int AIcountL = 0;
int AIcountR = 0;

int determineDirection(){
  
  long leftDist, rightDist, centerDist;
  int whichway;
 
 // Turns it's head left
 //waits for position and reads the value of the ultrasonic and saves it to leftDist (long)
  headServo.write(HEAD_SERVO_LEFT); 
  delay(1000);
  leftDist = ultrasonicSensor();
 
  //Turns it's head right does same thing for the left value
  headServo.write(HEAD_SERVO_RIGHT);
  delay(1000);
  rightDist = ultrasonicSensor();
 
  //returns the head to center
  headServo.write(HEAD_SERVO_CENTER);
  delay(1000);
  
  //finds out it's course of action
  if (AIcountL > 5 || AIcountR > 5){   //AIcount is variabes to make it back up if it is stuck in a corner.                         
    AIcountL = 0;                      // it sends a 2 to whichway variable and passes that to the main
    AIcountR = 0;
    return BACKUP; 
  }else{
    if (leftDist <= rightDist){  // favors turning right. if right returns a 0
       AIcountR = AIcountR + 1;
       return TURN_RIGHT;
    }else{
       AIcountL = AIcountL + 1;  //if left is greater then returns a 1
       return TURN_LEFT;
    }
  }
}

//-------------------------------------------[ultrasonic subs]---------------------------------------------------------------------
long ultrasonicSensor(){
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration, inches;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(ULTRASONIC_PIN, OUTPUT);
  digitalWrite(ULTRASONIC_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC_PIN, HIGH);
  delayMicroseconds(5);
  digitalWrite(ULTRASONIC_PIN, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(ULTRASONIC_PIN, INPUT);
  duration = pulseIn(ULTRASONIC_PIN, HIGH);

  // convert the time into a distance
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  inches = duration/ 72 / 2;
  return inches;
}

//----------------------------------[Accelerometer]--------------------------------------------------------------------------------

double getAcc_sigFigs(){
  double y = -1 * (analogRead(ACC_Y_PIN) * 3.3 / 1023 - 1.08) * 3.3 * 32.2; //ft/s^2

  int temp = y * 10; //remove non-sigfigs
  y = temp/10.0;  

  return y;
}

