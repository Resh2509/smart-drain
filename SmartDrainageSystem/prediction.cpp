// =====================================================
// AI-Based Smart Drainage Monitoring System
// Prediction Module Source
// ESP32 DevKit V1
// =====================================================

#include "prediction.h"

String predictDrainageStatus(
    float waterLevel,
    float pressure,
    float flowRate,
    float acoustic)
{
    // -----------------------------
    // Rule 1 : Flood Condition
    // -----------------------------
    if (waterLevel >= 90)
    {
        return "Flood";
    }

    // -----------------------------
    // Rule 2 : Blockage Detection
    // -----------------------------
    if (flowRate <= 10)
    {
        return "Blocked";
    }

    // -----------------------------
    // Rule 3 : Gas Warning
    // -----------------------------
    if (pressure >= 2.5 && acoustic >= 80)
    {
        return "Gas Warning";
    }

    // -----------------------------
    // Rule 4 : Warning
    // -----------------------------
    if (waterLevel >= 70 || pressure >= 2.0)
    {
        return "Warning";
    }

    // -----------------------------
    // Rule 5 : Normal
    // -----------------------------
    return "Normal";
}