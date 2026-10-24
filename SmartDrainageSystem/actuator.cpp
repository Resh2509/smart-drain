// =====================================================
// AI-Based Smart Drainage Monitoring System
// Actuator Manager Source
// ESP32 DevKit V1
// =====================================================

#include "actuator.h"
#include "config.h"

#include <ESP32Servo.h>

Servo ventServo;

// -----------------------------------------------------
// Initialize Actuators
// -----------------------------------------------------

void initializeActuators()
{
    pinMode(FAN_RELAY_PIN, OUTPUT);
    pinMode(PUMP_RELAY_PIN, OUTPUT);
    pinMode(STATUS_LED, OUTPUT);

    digitalWrite(FAN_RELAY_PIN, LOW);
    digitalWrite(PUMP_RELAY_PIN, LOW);
    digitalWrite(STATUS_LED, LOW);

    ventServo.attach(SERVO_PIN);
    ventServo.write(0);

    Serial.println("Actuators Initialized");
}

// -----------------------------------------------------
// Smart Auto Vent
// -----------------------------------------------------

void openVent()
{
    ventServo.write(90);

    Serial.println("Smart Auto Vent Opened");
}

void closeVent()
{
    ventServo.write(0);

    Serial.println("Smart Auto Vent Closed");
}

// -----------------------------------------------------
// Exhaust Fan
// -----------------------------------------------------

void fanON()
{
    digitalWrite(FAN_RELAY_PIN, HIGH);

    Serial.println("Exhaust Fan ON");
}

void fanOFF()
{
    digitalWrite(FAN_RELAY_PIN, LOW);

    Serial.println("Exhaust Fan OFF");
}

// -----------------------------------------------------
// Water Pump
// -----------------------------------------------------

void pumpON()
{
    digitalWrite(PUMP_RELAY_PIN, HIGH);

    Serial.println("Water Pump ON");
}

void pumpOFF()
{
    digitalWrite(PUMP_RELAY_PIN, LOW);

    Serial.println("Water Pump OFF");
}

// -----------------------------------------------------
// Status LED
// -----------------------------------------------------

void ledON()
{
    digitalWrite(STATUS_LED, HIGH);

    Serial.println("Status LED ON");
}

void ledOFF()
{
    digitalWrite(STATUS_LED, LOW);

    Serial.println("Status LED OFF");
}