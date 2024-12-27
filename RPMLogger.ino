#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RTClib.h>

extern Adafruit_SSD1306 display;
extern RTC_DS3231 rtc;
extern volatile int pulseCount;
extern unsigned long previousMillis, previousSaveMillis;
extern const long rpmInterval, saveInterval;
extern float rpm;

#define VOLTAGE_PIN 36

void IRAM_ATTR countPulse() {
  pulseCount++;
}

void handleRPMLogger() {
  DateTime now = rtc.now() + TimeSpan(0, 0, 0, 45);
  char timeString[9];
  char dateString[11];
  sprintf(timeString, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  sprintf(dateString, "%02d/%02d/%04d", now.day(), now.month(), now.year());

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= rpmInterval) {
    previousMillis = currentMillis;
    noInterrupts();
    rpm = (pulseCount * 60.0) / 20.0;
    pulseCount = 0;
    interrupts();
  }

  int analogValue = analogRead(VOLTAGE_PIN);
  float voltage = (float)analogValue / 4096.0 * 15.0 * 28205 / 27000;

  display.clearDisplay();
  display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);

  display.setCursor(2, 2);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print(timeString);

  display.setCursor(SCREEN_WIDTH - 65, 2);
  display.print(dateString);

  display.drawLine(0, 12, SCREEN_WIDTH, 12, WHITE);

  display.setTextSize(1);
  display.setCursor(20, 20);
  display.print("Nilai RPM : ");
  display.print(rpm, 2);

  display.setCursor(20, 30);
  display.print("Tegangan : ");
  display.print(voltage, 2);

  if (currentMillis - previousSaveMillis >= saveInterval) {
    previousSaveMillis = currentMillis;
    char dataString[50];
    sprintf(dataString, "Waktu: %s, RPM: %.2f, Tegangan: %.2f\n", timeString, rpm, voltage);
    writeFile(SD, "/RPMLOGGER.txt", dataString);

    display.setCursor(20, 40);
    display.print("Data disimpan!");
  } else {
    display.setCursor(20, 40);
    display.print("              "); // Clear text
  }

  display.display();
  delay(500);
}