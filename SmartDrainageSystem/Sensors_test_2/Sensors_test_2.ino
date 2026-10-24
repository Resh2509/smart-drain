/*
 * SmartDrain Full Hardware Test:
 * 1. YF-S201 Flow Sensor on GPIO 27 (via divider)
 * 2. JSN-SR04T Waterproof Ultrasonic Sensor on GPIO 12/13
 */

#include <NewPing.h> // Library for easier, non-blocking ultrasonic reading

// --- PIN DEFINITIONS ---
#define FLOW_SENSOR_PIN  27 // Connected to Point A (Divider safe output)
#define TRIGGER_PIN      12 // JSN-SR04T 'Trig' pin
#define ECHO_PIN         13 // JSN-SR04T 'Echo' pin
#define MAX_DISTANCE_CM  400 // Maximum sensor range (4 meters)

// --- SENSOR OBJECTS ---
// Initialize the NewPing library for the JSN-SR04T
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE_CM);

// --- GLOBAL VARIABLES ---
// Flow Sensor variables (Volatile is CRITICAL for interrupts)
volatile uint32_t flowPulseCount = 0;
float currentFlowRateLPM = 0.0;

// System timing variables
unsigned long oldTime = 0;
unsigned long samplingIntervalMs = 1000; // Read sensors every 1 second

// --- INTERRUPT SERVICE ROUTINE (ISR) ---
// This function runs INSTANTLY every time the flow sensor sends a pulse
void IRAM_ATTR pulseCounter() {
  flowPulseCount++;
}

void setup() {
  Serial.begin(115200);
  delay(2000); // Give user time to open Serial Monitor
  Serial.println("\n\n--- SmartDrain Multi-Sensor Test Starting ---");
  Serial.println("Monitoring both Flow and Water Level...\n");

  // 1. CONFIGURE FLOW SENSOR
  // Use INPUT_PULLUP to stabilize the signal, even with the voltage divider
  pinMode(FLOW_SENSOR_PIN, INPUT_PULLUP);
  // Attach interrupt on the FALLING edge (when signal drops from high to low)
  attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN), pulseCounter, FALLING);

  // 2. ULTRASONIC SENSOR (Handled by NewPing library, no setup needed)

  oldTime = millis();
}

void loop() {
  // Execute sensor readings once every interval (1 second)
  if ((millis() - oldTime) >= samplingIntervalMs) {

    // A. CALCULATE FLOW RATE
    // -------------------------------------------------------------
    // Atomic Copy: Stop interrupts, copy counter, reset, then restart.
    // This is crucial to prevent the counter changing mid-read.
    noInterrupts();
    uint32_t copiedPulses = flowPulseCount;
    flowPulseCount = 0;
    interrupts();

    // Calibration formula for YF-S201 (pulses/7.5 = LPM)
    currentFlowRateLPM = (float)copiedPulses / 7.5;

    // B. READ ULTRASONIC WATER LEVEL
    // -------------------------------------------------------------
    // sonar.ping_cm() returns the distance in centimeters.
    // It is a blocking call (pauses loop briefly), but is robust.
    int currentDistanceCm = sonar.ping_cm();

    // Handle "Out of Range" readings (0 usually means too far or too close)
    if (currentDistanceCm == 0) {
      Serial.print("Ultrasonic: Out of Range | ");
    } else {
      Serial.print("Water Depth (dist. from sensor): ");
      Serial.print(currentDistanceCm);
      Serial.print(" cm | ");
    }

    // C. PRINT RESULTS
    // -------------------------------------------------------------
    Serial.print("Flow Rate: ");
    Serial.print(currentFlowRateLPM, 2);
    Serial.println(" L/min");

    // Reset loop timer
    oldTime = millis();
  }

  // (The rest of your AI logic, XGBoost data logging, etc. would go here)
}