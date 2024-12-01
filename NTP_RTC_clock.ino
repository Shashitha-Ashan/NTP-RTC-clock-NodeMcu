
#include <FastLED.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>

const char* ssid = "yourSSID";
const char* password = "yourPASSWORD";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 0, 60000);

#define LED_PIN_1 D3
#define LED_PIN_2 D5
#define LED_PIN_3 D6
#define LED_PIN_4 D9

#define NUM_LEDS 14

#define CHIPSET WS2811
#define COLOR_ORDER GRB
CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
CRGB leds3[NUM_LEDS];
CRGB leds4[NUM_LEDS];

long Ctime = 0;
long Ptime = 0;
boolean LedState = LOW;

#define BRIGHTNESS 128


boolean numbers_pattern[10][7] = {
  { 1, 1, 1, 1, 1, 1, 0 },  //0
  { 0, 0, 0, 1, 1, 0, 0 },  //1
  { 1, 0, 1, 1, 0, 1, 1 },  //2
  { 0, 0, 1, 1, 1, 1, 1 },  //3
  { 0, 1, 0, 1, 1, 0, 1 },  //4
  { 0, 1, 1, 0, 1, 1, 1 },  //5
  { 1, 1, 1, 0, 1, 1, 1 },  //6
  { 0, 0, 1, 1, 1, 0, 0 },  //7
  { 1, 1, 1, 1, 1, 1, 1 },  //8
  { 0, 1, 1, 1, 1, 1, 1 },  //9

};
void setup() {
  pinMode(D13, OUTPUT);
  Serial.begin(115200);
  delay(3000);  // Safe dekay
  FastLED.addLeds<CHIPSET, LED_PIN_1, COLOR_ORDER>(leds1, NUM_LEDS).setCorrection(TypicalSMD5050);
  FastLED.addLeds<CHIPSET, LED_PIN_2, COLOR_ORDER>(leds2, NUM_LEDS).setCorrection(TypicalSMD5050);
  FastLED.addLeds<CHIPSET, LED_PIN_3, COLOR_ORDER>(leds3, NUM_LEDS).setCorrection(TypicalSMD5050);
  FastLED.addLeds<CHIPSET, LED_PIN_4, COLOR_ORDER>(leds4, NUM_LEDS).setCorrection(TypicalSMD5050);
  FastLED.setBrightness(BRIGHTNESS);


  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  timeClient.begin();
  Serial.println("Connected to WiFi");
}

void loop() {

  
  // seconds blink led
  Ctime = millis();
  if (Ctime - Ptime >= 1000) {
    digitalWrite(D13, !LedState);
    LedState = !LedState;
    Ptime = Ctime;
    timeClient.update();
  }
  int currentMinute = timeClient.getMinutes();
  int currentHour = timeClient.getHours();

  // hour display
  int hour_first_digit = currentHour / 10;
  display_hour_first_digit(hour_first_digit);
  int hour_second_digit = currentHour % 10;
  display_hour_second_digit(hour_second_digit);
  // minute display
  int min_first_digit = currentMinute / 10;
  display_min_first_digit(min_first_digit);
  int min_second_digit = currentMinute % 10;
  display_min_second_digit(min_second_digit);
  
  
}

void display_hour_first_digit(int no) {

  for (int i = 0; i < 7; i++) {
    if (numbers_pattern[no][i]) {
      leds1[i] = CRGB::Red;

    } else {
      leds1[i] = CRGB::Black;
    }
    FastLED.show();
  }
}
void display_hour_second_digit(int no) {

  for (int i = 0; i < 7; i++) {
    if (numbers_pattern[no][i]) {
      leds2[i] = CRGB::Red;

    } else {
      leds2[i] = CRGB::Black;
    }
    FastLED.show();
  }
}
void display_min_first_digit(int no) {

  for (int i = 0; i < 7; i++) {
    if (numbers_pattern[no][i]) {
      leds3[i] = CRGB::Red;

    } else {
      leds3[i] = CRGB::Black;
    }
    FastLED.show();
  }
}
void display_min_second_digit(int no) {
  for (int i = 0; i < 7; i++) {
    if (numbers_pattern[no][i]) {
      leds4[i] = CRGB::Red;

    } else {
      leds4[i] = CRGB::Black;
    }
    FastLED.show();
  }
}
