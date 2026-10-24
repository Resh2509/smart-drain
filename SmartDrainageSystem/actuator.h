#ifndef ACTUATOR_H
#define ACTUATOR_H

// =====================================================
// AI-Based Smart Drainage Monitoring System
// Actuator Manager Header
// ESP32 DevKit V1
// =====================================================

#include <Arduino.h>

// Initialize all actuators
void initializeActuators();

// Smart Auto Vent
void openVent();
void closeVent();

// Exhaust Fan
void fanON();
void fanOFF();

// Water Pump
void pumpON();
void pumpOFF();

// Status LED
void ledON();
void ledOFF();

#endif