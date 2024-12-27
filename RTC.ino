#include <RTClib.h>

extern RTC_DS3231 rtc;

void setupRTC() {
  if (!rtc.begin()) {
    Serial.println("RTC Error");
    while (true);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, setting the time!");
    // Uncomment the next line to set the RTC
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}