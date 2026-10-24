const int TRIG_PIN = 5;  // Connected to Trig
const int ECHO_PIN = 18; // Connected to Echo

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.println("AJ-SR04M Sensor Initialized. Place an object in front to test.");
}

void loop() {
  // Clear trigger pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Send a 10 microsecond HIGH pulse
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure response duration in microseconds (timeout at 30ms)
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0) {
    Serial.println("Reading out of range or sensor disconnected.");
  } else {
    // Distance calculation: (time * 0.0343 cm/us) / 2
    float distanceCm = (duration * 0.0343) / 2.0;
    Serial.print("Water Depth / Clearance: ");
    Serial.print(distanceCm, 1);
    Serial.println(" cm");
  }

  delay(500);
}