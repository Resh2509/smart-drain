#ifndef API_MANAGER_H
#define API_MANAGER_H

// =====================================================
// AI-Based Smart Drainage Monitoring System
// API Manager Header
// ESP32 DevKit V1
// =====================================================

#include <Arduino.h>

// Initialize API Manager
void initializeAPI();

// Send JSON data to FastAPI server
bool sendSensorData(String jsonData);

#endif