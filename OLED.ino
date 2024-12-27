#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 display;

void setupOLED() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
  display.clearDisplay();
}

void showLogo() {
  display.clearDisplay();
  display.drawBitmap(0, 0, myBitmap, 128, 64, WHITE);
  display.display();
  delay(1000);

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(40, 20);
  display.println("FIRE");
  display.setCursor(35, 40);
  display.println("FORCE");
  display.display();
  delay(2000);

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 10);
  display.println("Glenn Oriona Pane");
  display.setCursor(0, 20);
  display.println("Terbi Mutihari Setiawan");
  display.setCursor(0, 40);
  display.println("Vetracia Sharon");
  display.display();
  delay(2000);

  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(40, 20);
  display.println("RPM");
  display.setCursor(35, 40);
  display.println("LOGGER");
  display.display();
  delay(2000);

  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println("CEK");
  display.setCursor(0, 20);
  display.println("KOMPONEN...");
  display.display();
  delay(1000);

  display.clearDisplay();
  if (!rtc.begin()) {
    display.setCursor(10, 10);
    display.println("RTC:ERROR");
  } else {
    display.setCursor(10, 10);
    display.println("RTC:OK");
  }
  display.display();
  delay(500);

  display.clearDisplay();
  if (!SD.begin(SD_CS)) {
    display.setCursor(10, 20);
    display.println("SD Card: ERROR");
  } else {
    display.setCursor(10, 20);
    display.println("SDCard:OK");
  }
  display.display();
  delay(500);

  display.clearDisplay();
  pinMode(SENSOR_PIN, INPUT_PULLUP);
  if (digitalRead(SENSOR_PIN) == HIGH) {
    display.setCursor(10, 30);
    display.println("Sensor:OK");
  } else {
    display.setCursor(10, 30);
    display.println("Sensor:OK");
  }
  display.display();
  delay(2000);
}