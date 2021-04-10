/**
 * NetworkConfig
 * @author Curt Henrichs
 * @date 9-1-17
 *
 * Network Configuration file used to control library dependencies, conditional
 * compilation, and networking constants for application abstraction.
 */

#ifndef NETWORKCONFIG_H
#define NETWORKCONFIG_H

//==============================================================================
//                               Libraries
//==============================================================================

#include <Arduino.h>

//force these libraries for compatibility
#include <ESP.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

//==============================================================================
//                         Access Point Constants
//==============================================================================

const IPAddress AP_IP(192,168,0,1);
const IPAddress AP_GATEWAY(10,0,0,1);
const IPAddress AP_SUBNET(255,255,255,0);
const String AP_SSID("ORION");
const String AP_PASS("password");
const String ST_SSID("DC_GUEST");
const String ST_PASS("powering");

//==============================================================================
//                           Server Constants
//==============================================================================

#define HTML_SERVER_PORT        80
#define WEB_SOCKET_SERVER_PORT  5000

#endif
