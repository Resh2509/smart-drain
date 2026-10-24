#ifndef SENSORS_H
#define SENSORS_H

// =====================================================
// AI-Based Smart Drainage Monitoring System
// Sensor Manager Header File
// ESP32 DevKit V1
// =====================================================

#include <Arduino.h>

// Initialize all sensors
void initializeSensors();

// Read Water Level (cm)
float readWaterLevel();

// Read Pressure (kPa)
float readPressure();

// Read Flow Rate (L/min)
float readFlowRate();

// Read Acoustic Level (dB)
float readAcoustic();

#endif