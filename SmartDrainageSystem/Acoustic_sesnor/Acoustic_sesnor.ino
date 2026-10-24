const int MIC_PIN = 34; // GPIO 34 connected to Out pin

void setup() {
  Serial.begin(115200);
  delay(1000);
  analogReadResolution(12); // ESP32 12-bit ADC (0 - 4095)
  Serial.println("--- MAX9814 Acoustic Sensor Initialized ---");
  Serial.println("Tap the desk or make noise near the mic to test.");
}

void loop() {
  // Peak-to-peak measurement window (50 ms)
  unsigned long startMillis = millis();
  unsigned int peakToPeak = 0;
  unsigned int signalMax = 0;
  unsigned int signalMin = 4095;

  while (millis() - startMillis < 50) {
    int sample = analogRead(MIC_PIN);
    if (sample < 4095) {
      if (sample > signalMax) signalMax = sample;
      if (sample < signalMin) signalMin = sample;
    }
  }

  peakToPeak = signalMax - signalMin; // Amplitude / sound energy

  Serial.print("Acoustic Amplitude: ");
  Serial.print(peakToPeak);
  
  if (peakToPeak > 800) {
    Serial.println("  --> [SOUND SPIKE DETECTED!]");
  } else {
    Serial.println("  (Ambient / Normal)");
  }

  delay(200);
}