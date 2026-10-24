// =====================================================
// AI-Based Smart Drainage Monitoring System
// Sensor Manager Source File
// ESP32 DevKit V1
// =====================================================

#include "sensors.h"
#include "config.h"

// -----------------------------------------------------
// Initialize Sensors
// -----------------------------------------------------

void initializeSensors()
{
    Serial.println("=================================");
    Serial.println("Initializing Sensors...");
    Serial.println("=================================");

    // Configure sensor pins
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    pinMode(PRESSURE_PIN, INPUT);
    pinMode(ACOUSTIC_PIN, INPUT);
    pinMode(FLOW_SENSOR_PIN, INPUT);

    // Random number generator
    randomSeed(analogRead(0));

    Serial.println("All Sensors Initialized Successfully!");
    Serial.println("---------------------------------");
}

// -----------------------------------------------------
// Simulated Water Level
// Unit : cm
// -----------------------------------------------------

float readWaterLevel()
{
    return random(20, 101);
}

// -----------------------------------------------------
// Simulated Pressure
// Unit : kPa
// -----------------------------------------------------

float readPressure()
{
    return random(50, 300) / 100.0;
}

// -----------------------------------------------------
// Simulated Flow Rate
// Unit : L/min
// -----------------------------------------------------

float readFlowRate()
{
    return random(5, 50);
}

// -----------------------------------------------------
// Simulated Acoustic Level
// Unit : dB
// -----------------------------------------------------

float readAcoustic()
{
    return random(20, 95);
}