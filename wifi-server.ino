#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Adafruit_NeoPixel.h>

#include "index.h"
#include "wifi.h"

const char* ssid = _ssid;
const char* password = _password;

ESP8266WebServer server(80);
MDNSResponder mdns;

const int STRIP_LENGTH = 60;
const int PIN_NUMBER = 1; //D10
const int LED_BRIGHTNESS = 31;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRIP_LENGTH, PIN_NUMBER);

String page = file1;

uint32_t red = strip.Color(255,0,0);
uint32_t orange = strip.Color(255,127,0);
uint32_t yellow = strip.Color(255,255,0);
uint32_t green = strip.Color(0,255,0);
uint32_t blue = strip.Color(0,0,255);
uint32_t indigo = strip.Color(75,0,130);
uint32_t violet = strip.Color(148,0,211);
uint32_t black = strip.Color(0,0,0);

/*
 * 1.
 * Using a color picker, choose a custom colour
 * Create and name the colour here
 */
uint32_t myColor = strip.Color(255,127,31);

void setup() {
  setupWifi();
  setupServer();
  setupLed();
}

void loop() {
  server.handleClient();
}

/* ==================================================================== */

void custom1() {
  /*
   * 2.
   * Making the entire strip show custom colour
   */
   strip.showColor(myColor);
}

void custom2() {
  /*
   * 3.
   * Making the entire strip loop through a series of colours
   */
  uint32_t colors[] = {red, orange, yellow, green, blue, indigo, violet};


  int n = sizeof(colors)/sizeof(colors[0]);
  for (int i=0; i<STRIP_LENGTH; i++) strip.setPixelColor(i, colors[i%n]);
  strip.show();
}

/* ==================================================================== */

void setupWifi() {
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.begin(ssid, password); 
  delay(1000);

  while (WiFi.status() != WL_CONNECTED) {
    delay(200);

    //a flashing LED means the ESP is not connected
    digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
  }
  //a stable LED on means the ESP is now connected
  digitalWrite(LED_BUILTIN,true);

  mdns.begin("esp8266", WiFi.localIP());
}

void setupServer() {
  server.on("/", [](){
    server.send(200, "text/html", page);
  });
  
  server.on("/red", [](){
    server.send(200, "text/html", page);
    showColor(red);
  });

  server.on("/green", [](){
    server.send(200, "text/html", page);
    showColor(green);
  });

  server.on("/blue", [](){
    server.send(200, "text/html", page);
    showColor(blue);
  });

  server.on("/off", [](){
    server.send(200, "text/html", page);
    showColor(black);
  });

  server.on("/custom1", [](){
    server.send(200, "text/html", page);
    custom1();
  });

  server.on("/custom2", [](){
    server.send(200, "text/html", page);
    custom2();
  });
  
  server.begin();
}

void setupLed() {
  strip.begin();
  strip.show();
  strip.setBrightness(LED_BRIGHTNESS);
}

void showColor(uint32_t color) {
  for (int i=0; i<STRIP_LENGTH; i++) strip.setPixelColor(i,color);
  strip.show();
}

void showColor(uint8_t r, uint8_t g, uint8_t b) {
  for (int i=0; i<STRIP_LENGTH; i++) strip.setPixelColor(i,r,g,b);
  strip.show();
}
