#include <Wire.h>

void setup() {
  Serial.begin(115200);
  delay(1000);
  Wire.begin(21, 22); // SDA = GPIO 21, SCL = GPIO 22
  Serial.println("\n--- Testing BMP280 ---");
}

void loop() {
  Wire.beginTransmission(0x76);
  byte error = Wire.endTransmission();

  if (error == 0) {
    Serial.println("SUCCESS: Sensor detected at address 0x76! It is working perfectly.");
  } else {
    Wire.beginTransmission(0x77);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.println("SUCCESS: Sensor detected at address 0x77! It is working perfectly.");
    } else {
      Serial.println("Check: Ensure CSB is connected to 3.3V and pins are firmly seated.");
    }
  }
  delay(1000);
}