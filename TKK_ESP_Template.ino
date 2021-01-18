//sdm live page example by reaper7
//#define USE_STATIC_IP

/*  WEMOS D1 Mini
                     ______________________________
                    |   L T L T L T L T L T L T    |
                    |                              |
                 RST|                             1|TX HSer
                  A0|                             3|RX HSer
                  D0|16                           5|D1
                  D5|14                           4|D2
                  D6|12                    10kPUP_0|D3
RX SSer/HSer swap D7|13                LED_10kPUP_2|D4
TX SSer/HSer swap D8|15                            |GND
                 3V3|__                            |5V
                       |                           |
                       |___________________________|
*/

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>

#include <ESPAsyncTCP.h>                                                        //https://github.com/me-no-dev/ESPAsyncTCP
#include <ESPAsyncWebServer.h>                                                  //https://github.com/me-no-dev/ESPAsyncWebServer

#include "index_page.h"

//------------------------------------------------------------------------------
AsyncWebServer server(80);

//------------------------------------------------------------------------------
String devicename = "ESPTEMPLATE";

#if defined ( USE_STATIC_IP )
IPAddress ip(192, 168, 0, 130);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
#endif

const char* wifi_ssid = "ssid";
const char* wifi_password = "wifipass";

String lastresetreason = "";

//------------------------------------------------------------------------------
void indexrequest(AsyncWebServerRequest *request) {
  request->send_P(200, "text/html", index_page); 
}
//------------------------------------------------------------------------------
void ledOn() {
  digitalWrite(LED_BUILTIN, LOW);
}
//------------------------------------------------------------------------------
void ledOff() {
  digitalWrite(LED_BUILTIN, HIGH);
}
//------------------------------------------------------------------------------
void ledSwap() {
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}
//------------------------------------------------------------------------------
void otaInit() {
  ArduinoOTA.setHostname(devicename.c_str());

  ArduinoOTA.onStart([]() {
    ledOn();
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    ledSwap();
  });
  ArduinoOTA.onEnd([]() {
    ledOff();
  });
  ArduinoOTA.onError([](ota_error_t error) {
    ledOff();
  });
  ArduinoOTA.begin();
}
//------------------------------------------------------------------------------
void serverInit() {
  server.on("/", HTTP_GET, indexrequest);
  server.onNotFound([](AsyncWebServerRequest *request){
    request->send(404);
  });
  server.begin();
}
//------------------------------------------------------------------------------
static void wifiInit() {
  WiFi.persistent(false);                                                       // Do not write new connections to FLASH
  WiFi.mode(WIFI_STA);
#if defined ( USE_STATIC_IP )
  WiFi.config(ip, gateway, subnet);                                             // Set fixed IP Address
#endif
  WiFi.begin(wifi_ssid, wifi_password);

  while( WiFi.status() != WL_CONNECTED ) {                                      //  Wait for WiFi connection
    ledSwap();
    delay(100);
  }
}
//------------------------------------------------------------------------------
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  ledOn();

  lastresetreason = ESP.getResetReason();

  wifiInit();
  otaInit();
  serverInit();

  ledOff();
}
//------------------------------------------------------------------------------
void loop() {
  ArduinoOTA.handle();

  yield();
}
