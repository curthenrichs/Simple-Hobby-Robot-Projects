/**
 * Firmware
 * @author Curt Henrichs
 * @date 8-31-17
 *
 * Firmware for ORION-bot exposes a websocket interface that accepts JSON
 * messages to control the robot's drivetrain. A simple web server is also
 * employeed to allow control over the drivetrain without a dedicated
 * application.
 */
 
//==============================================================================
//                               Libraries
//==============================================================================

#include "HardwareConfig.h"
#include "NetworkConfig.h"
#include "Drivetrain.h"
#include "Webpage.h"


#include "RunningAverage.h"
#include <elapsedMillis.h>

//==============================================================================
//                         Constants and Macro Declaration
//==============================================================================

/**
 * Default size of tha running average window. Increasing this will increase the
 * memory foot.
 */
#define WATCHDOG_WINDOW_SIZE 10
/**
 * Average time between messages must be below this in order to not lockout motors
 */
#define WATCHDOG_TIME_THRESHOLD 75
/**
 * Switch between station and access point modes
 */
#define STATION_NOT_ACCESS false

//==============================================================================
//                           Private Attributes
//==============================================================================

/**
 * Webserver hosted on access point to allow for network ssid and password
 * configuration for this device
 */
static ESP8266WebServer server(HTML_SERVER_PORT);
/**
 * Websocket interface to drive the robot motors. This mechanism will allow
 * connection with any device that can do websocket as opposed to a slow
 * cluncky HTML form for control.
 */
static WebSocketsServer webSocket = WebSocketsServer(WEB_SOCKET_SERVER_PORT);
/**
 * Running average of packet times
 */
static RunningAverage _watchdog_connection_status(WATCHDOG_WINDOW_SIZE);
/**
 * Track time between messages starting at connection
 */
static elapsedMillis _watchdog_time_from_last;
/**
 * Drivetrain is set to move
 */
static bool _drivetrain_active;

//==============================================================================
//                        Private Function Prototypes
//==============================================================================

/**
 * Handles the index URI for this webserver. Responds by sending the application
 */
static void _handle_root(void);
/**
 * Handles any invalid request on this server.
 */
static void _handle_not_found(void);
/**
 * Handle web socket data event such as open, close, send text.
 * @param num is the socket that has event
 * @param type is the event type such as open, close, send text
 * @param payload is data if defined for type
 * @param len is the size of the payload in bytes
 */
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t len);
/**
 * Updates the motor watchdog, used to auto-disable if connection is bad
 */
void _feed_motor_watchdog(void);

//==============================================================================
//                                 MAIN
//==============================================================================

/**
 * Main intialization will setup the wifi connection and web server
 */
void setup() {

  _watchdog_connection_status.clear();
  _watchdog_connection_status.addValue(WATCHDOG_TIME_THRESHOLD/2); //remove nan
  _watchdog_time_from_last = 0;
  _drivetrain_active = false;

#if DEBUGGING_MODE
  Serial.begin(115200);
  Serial.println("Starting Serial Debugger");
#endif

  drive_init(LEFT_MOTOR_PIN,RIGHT_MOTOR_PIN);

#if STATION_NOT_ACCESS
  WiFi.begin(ST_SSID.c_str(),ST_PASS.c_str());

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("success!");

  Serial.print("IP Address is: ");
  Serial.print(WiFi.localIP());
#else
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(AP_IP,AP_GATEWAY,AP_SUBNET);
  WiFi.softAP(AP_SSID.c_str(),AP_PASS.c_str());

#if DEBUGGING_MODE
  Serial.print("Soft AP IP : ");
  Serial.println(WiFi.softAPIP());
#endif

#endif


  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

  server.on("/",_handle_root);
  server.onNotFound(_handle_not_found);
  server.begin();

#if DEBUGGING_MODE
  Serial.println("Starting server");
#endif
}

/**
 * Main loop will handle webserver requests which will either give an app to
 * requester or update the drivetrain
 */
void loop() {
  server.handleClient();
  webSocket.loop();

  if(_watchdog_locked_out() && _drivetrain_active){
    drive_hard_stop();
    _drivetrain_active = false;
#if DEBUGGING_MODE
    Serial.println("Motor lockout");
#endif
  }
}

//==============================================================================
//                         Private Function Implementation
//==============================================================================

/**
 * Handles the index URI for this webserver. Responds with configuration page.
 */
static void _handle_root(void) {
#if DEBUGGING_MODE
  Serial.println("Handle root");
#endif

  server.send(200, "text/html", ROOT_WEBPAGE);
}

/**
 * Handles any invalid request on this server.
 */
static void _handle_not_found(void){
#if DEBUGGING_MODE
  Serial.println("Handle not found");
#endif

  String message = "Webpage not found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

/**
 * Handle web socket data event such as open, close, send text.
 * @param num is the socket that has event
 * @param type is the event type such as open, close, send text
 * @param payload is data if defined for type
 * @param len is the size of the payload in bytes
 */
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t len){
  switch(type) {
    case WStype_DISCONNECTED:
#if DEBUGGING_MODE
      Serial.printf("[%u] Disconnected!\n", num);
#endif
      drive_hard_stop();
      _drivetrain_active = false;
      _watchdog_connection_status.clear();
      _watchdog_connection_status.addValue(WATCHDOG_TIME_THRESHOLD/2); //remove nan
      break;
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
#if DEBUGGING_MODE
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n",
            num, ip[0], ip[1], ip[2], ip[3], payload);
#endif
        // send message to client
        webSocket.sendTXT(num, "{\"connected\":true}");
        _watchdog_time_from_last = 0;
        _watchdog_connection_status.clear();
      }
      break;
    case WStype_TEXT:
      {
        //parse JSON message
        DynamicJsonBuffer buffer;
        JsonObject& root = buffer.parseObject(payload);
        if(root.success()){
#if DEBUGGING_MODE
          Serial.println("Successfully parsed JSON message");
#endif
          if(root["stop"]){
            //hard stop motors, disregard rest of message as this is needed now!
            drive_hard_stop();
            _feed_motor_watchdog();
            _drivetrain_active = false;
          }else if(root["connection"]){
            //connection packet that disables watchdog for a period of time
            _feed_motor_watchdog();
          }else if(!_watchdog_locked_out()){
            //parse x,y coordinates to drive motors
            float x = root["x"];
            float y = root["y"];
            drive_cartesian((int)(x),(int)(y));
            _feed_motor_watchdog();
            _drivetrain_active = true;
          }else{
            drive_hard_stop();
          }
        }else{
#if DEBUGGING_MODE
          Serial.println("Failed to parse JSON message");
#endif
        }
      }
      break;
    default:
      break;
  }
}

/**
 * Updates the motor watchdog, used to auto-disable if connection is bad
 */
void _feed_motor_watchdog(void){
  _watchdog_connection_status.addValue(_watchdog_time_from_last);
  _watchdog_time_from_last = 0;
}

/**
 * Determines whether the watchdog is currently locking motor control
 */
bool _watchdog_locked_out(void){
  return _watchdog_connection_status.getAverage() > WATCHDOG_TIME_THRESHOLD;
}
