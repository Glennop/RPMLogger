#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RTClib.h>
#include "FS.h"
#include "SD.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define SENSOR_PIN 33
#define VOLTAGE_PIN 36
#define SD_CS 5

RTC_DS3231 rtc;
volatile int pulseCount = 0;
unsigned long previousMillis = 0;
const long rpmInterval = 1000;
float rpm = 0;
unsigned long previousSaveMillis = 0;
const long saveInterval = 5000;

// Include custom bitmap
#include "bitmap.h"

// Function declarations
void writeFile(fs::FS &fs, const char *path, const char *message);
void IRAM_ATTR countPulse();
void showLogo();
void setupOLED();
void setupRTC();
void setupSD();

void setup() {
  Serial.begin(9600);

  setupOLED();
  showLogo();
  setupRTC();
  setupSD();

  pinMode(SENSOR_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), countPulse, FALLING);
}

void loop() {
  handleRPMLogger();
}