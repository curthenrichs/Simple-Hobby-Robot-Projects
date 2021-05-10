/**
 * Bubbles Firmware
 * @author Curt Henrichs
 * @date 6-25-17
 *
 * Firmware for Bubbles robot platform. Software exposes a manual operation
 * mode and an autonomous mode. Commands are entered through the XBee device.
 * Commands are encoded in JSON strings for ease of parsing.
 *
 * JSON from Client to Bubbles ('/0' deliminates message over serial)
 *  {
 *    "color": {"r": #=<0-255>, "g": #=<0-255>, "b": #=<0-255>},
 *    "mode": "#=<manual, auton, off>",
 *    "manual command": "#=<stop,forward,backward,left forward,left backward,
 *                          right forward, right backward>",
 *    "neck position": #=<0-180>,
 *    "get control data": #=<true,false>,
 *    "get distance": #=<true,false>,
 *    "get color": #=<true,false>,
 *    "get neck position": #=<true,false>,
 *    "uuid": #=<(unsigned integer ID)>
 *  }/0
 *
 * JSON from Bubbles to clients ('/0' deliminates message over serial)
 *  {
 *    "uuid": #=<unsigned integer ID>,
 *    "control":
 *    {
 *        "mode": "#=<manual, auton, off>",
 *        "manual command": "#=<stop,forward,backward,left forward,
 *                              left backward,right forward, right backward>",
 *        "neck position": #=<0-180>,
 *        "color": {"r": #=<0-255>, "g": #=<0-255>, "b": #=<0-255>}
 *    },
 *    "distance": #=<long integer>,
 *    "color": {"r": #=<0-255>, "g": #=<0-255>, "b": #=<0-255>},
 *    "neck position": #=<1-180>,
 *    "bubbles alive": #<true,false>
 *  }/0
 */

//TODO reenable neck only when power is figured out.
//TODO solder bubbles xbee rx pin back on
//TODO debug blue LED channel

//==============================================================================
//                               Libraries
//==============================================================================

#include <SoftwareSerial.h>
#include "HardwareConfig.h"
#include "BubblesHardware.h"
#include "Autonomous.h"
#include <ArduinoJson.h>
#include <elapsedMillis.h>

//==============================================================================
//                         Constant and Macro Definition
//==============================================================================

/**
 * Defines the possible states of the firmware.
 */
typedef enum Mode {
  OFF,      //<! not actively controlling Bubbles (Hardware roams free)
  MANUAL,   //<! manual control of Bubbles expects periodic commands
  AUTON     //<! autonomous control of Bubbles runs "wall-banger" algorithm
} Mode_e;

/**
 * Defines the possible commands sent over JSON for manual control
 */
typedef enum CommandedMovement {
  STOP,
  FORWARD,
  BACKWARD,
  LEFT_FORWARD,
  LEFT_BACKWARD,
  RIGHT_FORWARD,
  RIGHT_BACKWARD
} CommandedMovement_e;

// JSON parse Constants
#define MIN_JSON_PACKET_SIZE 5
#define END_OF_MSG_CHAR '\0'
#define TIMEOUT_TIME 100 //ms

//Connection Time
#define DISCONNET_TIME 5000 //ms

// Preset Colors
#define AUTON_LED_COLOR RED
#define OFF_LED_COLOR BLACK

// Preset Neck Positions
#define AUTON_NECK_POSITION NECK_MIN_POS
#define OFF_NECK_POSITION NECK_MIN_POS

//==============================================================================
//                        Data Structure Declaration
//==============================================================================

/**
 * Control variables (states) for Bubbles firmware.
 */
typedef struct BubblesControl {
  int neckPos;
  Mode_e mode;
  CommandedMovement_e manualCommand;
  Color_t color;
} BubblesControl_t;

//==============================================================================
//                            Private Members
//==============================================================================

//Physical Objects
static SoftwareSerial _xbee(XBEE_RX_PIN, XBEE_TX_PIN);
static BubblesHardware _bubblesHardware;

//Control Structure
static BubblesControl_t _control = {
  .neckPos = NECK_MIN_POS,
  .mode = OFF,
  .manualCommand = STOP,
  .color = WHITE
};

//Timers
static elapsedMillis _timeoutTimer;
static elapsedMillis _uuidGenerator;
static elapsedMillis _disconnectTimer;

//JSON String Buffers
static char _txStr[100];
static char _rxStr[100];
static StaticJsonBuffer<200> _rxBuffer;
static StaticJsonBuffer<200> _txBuffer;

//==============================================================================
//                       Private Function Prototypes
//==============================================================================

/**
 * Reads a string from the xbee serial. If string is in buffer then it is parsed
 * for JSON content. If timeout then message is still attempted to be parsed.
 * Successful parsing of JSON may update the state variables or send data
 * back to requester.
 */
static void _readStringFromXbee(void);

/**
 * Parses a prebuild (successful) JSON object for the data relevant to the
 * Bubbles control system. Specifically data that is being handled follows
 * patterns:
 *      -> "color": {"r": #, "g": #, "b": #} --where # is number from 0 to 255
 *      -> "mode": #     --where # is "off", "manual", or "auton"
 *      -> "manual command": #  --where # is "stop", "forward", "backward",
 *                                           "left forward",  "right forward"
 *                                           "left backward", "right backward"
 *      -> "neck position": #  --where # is position from 0 to 180 degrees
 *      -> "get control data": # --where # is true or false
 *      -> "get distance": # --where # is true or false
 *      -> "get color": # --where # is true or false
 *      -> "get neck position": --where # is true or false
 *      -> "uuid": # --where # is ID number for message
 * @param rxRoot is successfully constructed JSON tree to collect data from
 */
static void _parseJSONobject(JsonObject& rxRoot);

/**
 * Produces an ACK back to the requester. Additionly if any get requests were
 * in the JSON string then that data is collected and sent with the ACK.
 * @param rxRoot is receive JSON root node for determining any get requests
 */
 static void _respondJSON(JsonObject& rxRoot);

 /**
  * Produce a JSON message to anything listening on xbee serial connection.
  * Message is an alive signal which should be periodically sent when no messages
  * are being receieved to let another device know of this device's existence.
  */
 static void _aliveJSON(void);

//==============================================================================
//                                MAIN
//==============================================================================

/**
 * Setup initializes hardware and software modules. Starts xbee communication.
 * If off then disables the motor controller, else if on (auto/manual) then
 * enables motor controller.
 */
void setup(void){

  // module initialization
  Serial.begin(9600);
  _xbee.begin(XBEE_BAUD);
  _xbee.listen();
  auto_reset();

  //determine if drivetrain is enabled
  if(_control.mode == OFF){
    //intial mode is off so disable the motor controller
    _bubblesHardware.disableControl(true);
  }else{
    //initial mode is on so enable motors
    _bubblesHardware.disableControl(false);
  }
  Serial.println(F("Testing"));
}

/**
 * Main loop implements a state machine of OFF, AUTON, and MANUAL. Each state
 * updates the hardware approproatly. Additionaly JSON messages are receieved
 * periodically for control update from requester. If no JSON message has been
 * received for a significant period of time then periodic "life" JSON messages
 * are sent out to notify clients of this devices existence.
 *
 * Hardware control includes:
 *    -> Neck Servo
 *    -> Head LEDs
 *    -> Drivetrain movement.
 */
void loop(void){
  //get message from xbee serial
  if(_xbee.available() > MIN_JSON_PACKET_SIZE){
    _readStringFromXbee();
    _disconnectTimer = 0;
  }

  //determine if no message in a long time. Then be considered disconnected
  if(_disconnectTimer >= DISCONNET_TIME && _control.mode == MANUAL){
      // need to turn off robot due to disconnect and in maunal drive mode
      _control.mode = OFF;
      _bubblesHardware.disableControl(true);
  }else if(_disconnectTimer >= DISCONNET_TIME){
      //pulse out an alive message to see if a device knows that device is on
      _aliveJSON();
      _disconnectTimer -= DISCONNET_TIME; //prevent rollover
  }

  //handle low level hardware updates
  _bubblesHardware.getRelayBoard().update();

  //state select
  switch(_control.mode){
    case OFF:
      _bubblesHardware.getNeckServo().write(OFF_NECK_POSITION);
      _bubblesHardware.getLED().setColor(OFF_LED_COLOR);
      break;
    case MANUAL:
      _bubblesHardware.getNeckServo().write(_control.neckPos);
      //_bubblesHardware.getLED().setColor(_control.color);
      switch(_control.manualCommand){
        case STOP:
          _bubblesHardware.stopMoving();
          break;
        case FORWARD:
          _bubblesHardware.forward();
          break;
        case BACKWARD:
          _bubblesHardware.backward();
          break;
        case LEFT_FORWARD:
          _bubblesHardware.forwardLeft();
          break;
        case LEFT_BACKWARD:
          _bubblesHardware.backwardLeft();
          break;
        case RIGHT_FORWARD:
          _bubblesHardware.forwardRight();
          break;
        case RIGHT_BACKWARD:
          _bubblesHardware.backwardRight();
          break;
        default:
          //error state set command to STOP
          _control.manualCommand = STOP;
          break;
      }
      break;
    case AUTON:
      auto_update(_bubblesHardware);
      _bubblesHardware.getNeckServo().write(AUTON_NECK_POSITION);
      //_bubblesHardware.getLED().setColor(AUTON_LED_COLOR);
      delay(50);
      break;
    default:
      //error state set mode to OFF
      _control.mode = OFF;
      break;
  }
}

//==============================================================================
//                        Private Function Implementation
//==============================================================================

/**
 * Reads a string from the xbee serial. If string is in buffer then it is parsed
 * for JSON content. If timeout then message is still attempted to be parsed.
 * Successful parsing of JSON may update the state variables or send data
 * back to requester.
 */
static void _readStringFromXbee(void){
  bool endStr = false;
  int i = 0;
  _timeoutTimer = 0;
  while((_timeoutTimer < TIMEOUT_TIME) && !endStr && (i < sizeof(_rxStr)-1)){
    if(_xbee.available()){
      _rxStr[i] = _xbee.read();
      endStr = (_rxStr[i] == END_OF_MSG_CHAR);
      i++;
    }
  }
  //attempt to parse string as JSON
  _rxBuffer.clear();
  JsonObject& root = _rxBuffer.parseObject(_rxStr);
  if(root.success() && root.containsKey("U")){
    _parseJSONobject(root);
  }
}

/**
 * Parses a prebuild (successful) JSON object for the data relevant to the
 * Bubbles control system. Specifically data that is being handled follows
 * patterns:
 *      -> "color": {"r": #, "g": #, "b": #} --where # is number from 0 to 255
 *      -> "mode": #     --where # is "off", "manual", or "auton"
 *      -> "manual command": #  --where # is "stop", "forward", "backward",
 *                                           "left forward",  "right forward"
 *                                           "left backward", "right backward"
 *      -> "neck position": #  --where # is position from 0 to 180 degrees
 *      -> "get control data": # --where # is true or false
 *      -> "get distance": # --where # is true or false
 *      -> "get color": # --where # is true or false
 *      -> "get neck position": --where # is true or false
 *      -> "uuid": # --where # is ID number for message
 * @param rxRoot is successfully constructed JSON tree to collect data from
 */
static void _parseJSONobject(JsonObject& rxRoot){
  //extract data from JSON
  if(rxRoot.containsKey("Cr")){
    _control.color.r = rxRoot["Cr"]["r"];
    _control.color.g = rxRoot["Cr"]["g"];
    _control.color.b = rxRoot["Cr"]["b"];
  }
  if(rxRoot.containsKey("Mo")){
    const char* str = rxRoot["Mo"].asString();
    if(strcmp(str,"off") == 0){
      if(_control.mode != OFF){
        _bubblesHardware.disableControl(true);
        _control.mode = OFF;
      }
    }else if(strcmp(str,"manual") == 0){
      if(_control.mode != MANUAL){
        _bubblesHardware.disableControl(false);
        _control.mode = MANUAL;
      }
    }else if(strcmp(str,"auton") == 0){
      if(_control.mode != AUTON){
        _bubblesHardware.disableControl(false);
        auto_reset();
        _control.mode = AUTON;
      }
    }else{
      //erring on side of caution, setting mode to off
      _control.mode = OFF;
    }
  }
  if(rxRoot.containsKey("Dr")){
    const char* str = rxRoot["Dr"].asString();
    if(strcmp(str,"stop") == 0){
      _control.manualCommand = STOP;
    }else if(strcmp(str,"forward") == 0){
      _control.manualCommand = FORWARD;
    }else if(strcmp(str,"backward") == 0){
      _control.manualCommand = BACKWARD;
    }else if(strcmp(str,"left forward") == 0){
      _control.manualCommand = LEFT_FORWARD;
    }else if(strcmp(str,"right forward") == 0){
      _control.manualCommand = RIGHT_FORWARD;
    }else if(strcmp(str,"left backward") == 0){
      _control.manualCommand = LEFT_BACKWARD;
    }else if(strcmp(str,"right backward") == 0){
      _control.manualCommand = RIGHT_BACKWARD;
    }else{
      //erring on side of caution, setting command to stop
      _control.manualCommand = STOP;
    }
  }
  if(rxRoot.containsKey("Np")){
    _control.neckPos = rxRoot["Np"].as<int>();
  }

  // ACK back to requester
  _respondJSON(rxRoot);

}

/**
 * Produces an ACK back to the requester. Additionly if any get requests were
 * in the JSON string then that data is collected and sent with the ACK.
 * @param rxRoot is receive JSON root node for determining any get requests
 */
static void _respondJSON(JsonObject& rxRoot){
  //produce ACK message
  _txBuffer.clear();
  JsonObject& txRoot = _txBuffer.createObject();
  txRoot["U"] =  rxRoot["U"];

  //if requester wants control data back
  if(rxRoot["GCD"]){
    JsonObject& ctrl = txRoot.createNestedObject("CD");

    //package up current data and send back to requester
    const char* modeStr = "";
    switch(_control.mode){
      case OFF:
        modeStr = "off";
        break;
      case AUTON:
        modeStr = "auton";
        break;
      case MANUAL:
        modeStr = "manual";
        break;
    }
    ctrl["Mo"] = modeStr;
    const char* cmdStr = "";
    switch(_control.manualCommand){
      case STOP:
        cmdStr = "stop";
        break;
      case FORWARD:
        cmdStr = "forward";
        break;
      case BACKWARD:
        cmdStr = "backward";
        break;
      case LEFT_FORWARD:
        cmdStr = "left forward";
        break;
      case RIGHT_FORWARD:
        cmdStr = "right forward";
        break;
      case LEFT_BACKWARD:
        cmdStr = "left backward";
        break;
      case RIGHT_BACKWARD:
        cmdStr = "right backward";
        break;
    }
    ctrl["Dr"] = cmdStr;
    ctrl["Np"] = _control.neckPos;
    JsonObject& color = ctrl.createNestedObject("Cr");
    color["r"] = _control.color.r;
    color["g"] = _control.color.g;
    color["b"] = _control.color.b;
  }

  //if requester wants ultrasonic distance back
  if(rxRoot["GDi"]){
    txRoot["Di"] = _bubblesHardware.getUltrasonic().getDistance();
  }

  //if requester wants actual color
  if(rxRoot["GCr"]){
    JsonObject& color = txRoot.createNestedObject("Cr");

    Color_t c;
    switch(_control.mode){
      case OFF:
        c = OFF_LED_COLOR;
        break;
      case AUTON:
        c = AUTON_LED_COLOR;
        break;
      case MANUAL:
        c = _control.color;
        break;
    }
    color["r"] = c.r;
    color["g"] = c.g;
    color["b"] = c.b;
  }

  //if requester wants actual neck position
  if(rxRoot["GNp"]){
    int position = 0;
    switch(_control.mode){
      case OFF:
        position = OFF_NECK_POSITION;
        break;
      case AUTON:
        position = AUTON_NECK_POSITION;
        break;
      case MANUAL:
        position = _control.neckPos;
        break;
    }
    txRoot["Np"] = position;
  }

  //send message
  txRoot.printTo(_txStr,sizeof(_txStr));
  _xbee.print(_txStr);
  _xbee.print(END_OF_MSG_CHAR);
}

/**
 * Produce a JSON message to anything listening on xbee serial connection.
 * Message is an alive signal which should be periodically sent when no messages
 * are being receieved to let another device know of this device's existence.
 */
static void _aliveJSON(void){
  _txBuffer.clear();
  JsonObject& txRoot = _txBuffer.createObject();
  txRoot["BA"] = true;
  uint32_t uuid;
  txRoot["U"] = uuid = _uuidGenerator;
  txRoot.printTo(_txStr,sizeof(_txStr));
  _xbee.print(_txStr);
  _xbee.print(END_OF_MSG_CHAR);
}
