// Pin connected to the Flow Sensor's Yellow signal wire
const int SENSOR_PIN = 4;

// Calibration factor for YF-S201: pulses per second per (L/min)
// F = 7.5 * Q (where Q is flow rate in L/min)
const float CALIBRATION_FACTOR = 7.5;

volatile unsigned long pulseCount = 0;
float flowRate = 0.0;
unsigned int flowMilliLitres = 0;
unsigned long totalMilliLitres = 0;
unsigned long previousMillis = 0;

// Interrupt Service Routine (ISR) to count pulses
void IRAM_ATTR pulseCounter() {
  pulseCount++;
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Configure sensor pin with internal pullup
  pinMode(SENSOR_PIN, INPUT_PULLUP);

  // Attach interrupt: runs pulseCounter() every time pin goes LOW to HIGH
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), pulseCounter, RISING);

  Serial.println("--- YF-S201 Flow Sensor Initialized ---");
  Serial.println("Blow into the sensor or run water to test.");
}

void loop() {
  unsigned long currentMillis = millis();

  // Calculate flow every 1000 ms (1 second)
  if (currentMillis - previousMillis >= 1000) {
    // Temporarily detach interrupt while reading shared variable
    detachInterrupt(digitalPinToInterrupt(SENSOR_PIN));

    // Calculate flow rate in Liters/minute:
    // Frequency (Hz) / 7.5 = Flow rate (L/min)
    flowRate = ((1000.0 / (currentMillis - previousMillis)) * pulseCount) / CALIBRATION_FACTOR;
    
    // Convert L/min to volume passed in this 1-second interval
    flowMilliLitres = (flowRate / 60.0) * 1000.0;
    totalMilliLitres += flowMilliLitres;

    // Reset pulse counter and timer
    pulseCount = 0;
    previousMillis = currentMillis;

    // Reattach interrupt to keep counting
    attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), pulseCounter, RISING);

    // Print values to Serial Monitor
    Serial.print("Current Flow Rate: ");
    Serial.print(flowRate, 2);
    Serial.print(" L/min | Total Volume: ");
    Serial.print(totalMilliLitres);
    Serial.println(" mL");
  }
}