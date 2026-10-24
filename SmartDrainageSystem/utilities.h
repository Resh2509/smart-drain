#ifndef UTILITIES_H
#define UTILITIES_H

// =====================================================
// AI-Based Smart Drainage Monitoring System
// Utilities Header
// ESP32 DevKit V1
// =====================================================

#include <Arduino.h>

// Print startup information
void printSystemInfo();

// Blink onboard LED
void blinkLED(int times, int delayTime);

// Restart ESP32
void restartESP();

// Print free heap memory
void printMemory();

// Print formatted message
void debugPrint(String message);

#endif