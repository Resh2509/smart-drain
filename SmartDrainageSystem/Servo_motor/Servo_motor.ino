/*
 * MG996R Servo Motor Functional Test
 * Signal Wire (Orange) connected to ESP32 Pin GPIO 13
 */

const int SERVO_PIN = 13;

// Function to send standard PWM pulses to position the servo
void setServoAngle(int angle) {
  int pulseWidth = map(angle, 0, 180, 500, 2400);

  // Send 25 refresh pulses (~500ms duration) so the gear completes the turn
  for (int i = 0; i < 25; i++) {
    digitalWrite(SERVO_PIN, HIGH);
    delayMicroseconds(pulseWidth);
    digitalWrite(SERVO_PIN, LOW);
    delayMicroseconds(20000 - pulseWidth); // 20ms period (50Hz)
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  pinMode(SERVO_PIN, OUTPUT);

  Serial.println("\n--- MG996R Servo Actuator Test Running ---");
  Serial.println("Moving to 0 degrees (Vent CLOSED)...");
  setServoAngle(0);
  delay(1500);
}

void loop() {
  // Move to 60 degrees (Auto-Vent OPEN)
  Serial.println("Action: Moving to 60° (Vent Flap OPEN)");
  setServoAngle(60);
  delay(2000);

  // Move back to 0 degrees (Auto-Vent CLOSED)
  Serial.println("Action: Moving to 0° (Vent Flap CLOSED)");
  setServoAngle(0);
  delay(2000);

  // Move to 90 degrees (Vent FULLY OPEN)
  Serial.println("Action: Moving to 90° (Vent FULLY OPEN)");
  setServoAngle(90);
  delay(2000);

  // Return to 0 degrees
  Serial.println("Action: Returning to 0° (Vent CLOSED)");
  setServoAngle(0);
  delay(2000);
}