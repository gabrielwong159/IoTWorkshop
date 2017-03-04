#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>

#include "index.h"

//Variable Assignment
String wifiName = "Gabriel's Wifi";
const char WiFiAPPSK[] = "password1";

const int STRIP_LENGTH = 8;
const int PIN_NUMBER = 1; //D10
const int LED_BRIGHTNESS = 255;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRIP_LENGTH, PIN_NUMBER);

uint32_t red = strip.Color(255,0,0);
uint32_t orange = strip.Color(255,127,0);
uint32_t yellow = strip.Color(255,255,0);
uint32_t green = strip.Color(0,255,0);
uint32_t blue = strip.Color(0,0,255);
uint32_t indigo = strip.Color(75,0,130);
uint32_t violet = strip.Color(148,0,211);
uint32_t black = strip.Color(0,0,0);

void custom1() {
  uint32_t myColor1 = strip.Color(255, 127, 0); //call colour function
  uint32_t myColor2 = strip.Color(0, 127, 255);
  uint32_t myColors[] = {red, green, blue};
  //use loop to iterate through mycolors[]

  int num = random(2);
  
  if (num == 0) {
    showColor(myColor1);
  }
  else {
    showColor(myColor2);
  }
}

/* ==================================================================================== */

WiFiServer server(80);

void setup() 
{
  setupWiFi();
  setupLed();
  server.begin();
}

void loop() 
{
  WiFiClient client = server.available();
  if (!client) return;

  String req = client.readStringUntil('\r');
  client.flush();

  if (req.indexOf("/red") != -1)  showColor(red);
  else if (req.indexOf("/green") != -1) showColor(green);
  else if (req.indexOf("/blue") != -1) showColor(blue);
  else if (req.indexOf("/rainbow") != -1) showRainbow();
  else if (req.indexOf("/off") != -1) showColor(black);
  else if (req.indexOf("/custom1") != -1) custom1();

  client.flush();
  
  client.print(file1);
  delay(1);
}


void setupWiFi() {
  WiFi.mode(WIFI_AP);

  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) +
                 String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  String AP_NameString = wifiName;

  char AP_NameChar[AP_NameString.length() + 1];
  memset(AP_NameChar, 0, AP_NameString.length() + 1);

  for (int i=0; i<AP_NameString.length(); i++)
    AP_NameChar[i] = AP_NameString.charAt(i);

  WiFi.softAP(AP_NameChar, WiFiAPPSK);
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

void showRainbow() {
  uint32_t colors[] = {violet, indigo, blue, green, yellow, orange, red};
  int n = sizeof(colors)/sizeof(colors[0]);

  for (int i=0; i<STRIP_LENGTH; i++) strip.setPixelColor(i, colors[i%n]);
  strip.show();
}
