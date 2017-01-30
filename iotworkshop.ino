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

boolean rainbow = false;

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
  custom3();
  server.handleClient();
}

/* ==================================================================== */

void custom1() {
  /*
   * 2.
   * Making the entire strip show custom colour
   */
   showColor(myColor);
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

void custom3() {
  uint32_t colors[] = {violet, indigo, blue, green, yellow, orange, red};
  int n = sizeof(colors)/sizeof(colors[0]);

  for (int i=0; i<STRIP_LENGTH; i++) {
    for (int j=0; j<STRIP_LENGTH; j++) {
      server.handleClient();
      if(!rainbow) break;
      
      strip.setPixelColor((i+j)%STRIP_LENGTH, colors[j%n]);
    }
    strip.show();
    delay(100);
  }
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
    servePage();
  });
  
  server.on("/red", [](){
    servePage();
    showColor(red);
  });

  server.on("/green", [](){
    servePage();
    showColor(green);
  });

  server.on("/blue", [](){
    servePage();
    showColor(blue);
  });

  server.on("/off", [](){
    servePage();
    showColor(black);
  });

  server.on("/custom1", [](){
    servePage();
    custom1();
  });

  server.on("/custom2", [](){
    servePage();
    custom2();
  });

  server.on("/custom3", [](){
    servePage();
    rainbow = true;
  });
  
  server.begin();
}

void setupLed() {
  strip.begin();
  strip.show();
  strip.setBrightness(LED_BRIGHTNESS);
}

void servePage() {
  rainbow = false;
  server.send(200, "text/html", page);
}

void showColor(uint32_t color) {
  for (int i=0; i<STRIP_LENGTH; i++) strip.setPixelColor(i,color);
  strip.show();
}

void showColor(uint8_t r, uint8_t g, uint8_t b) {
  for (int i=0; i<STRIP_LENGTH; i++) strip.setPixelColor(i,r,g,b);
  strip.show();
}
