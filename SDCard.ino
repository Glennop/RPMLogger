#include "FS.h"
#include "SD.h"

#define SD_CS 5

void setupSD() {
  if (!SD.begin(SD_CS)) {
    Serial.println("SD Card Error");
    while (true);
  }
}

void writeFile(fs::FS &fs, const char *path, const char *message) {
  File file = fs.open(path, FILE_APPEND);
  if (!file) {
    Serial.println("Failed to open file for appending");
    return;
  }

  if (file.print(message)) {
    Serial.println("Data appended");
  } else {
    Serial.println("Append failed");
  }

  file.close();
}