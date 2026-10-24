// =====================================================
// AI-Based Smart Drainage Monitoring System
// JSON Manager Source File
// ESP32 DevKit V1
// =====================================================

#include "json_manager.h"
#include "config.h"

String createSensorJSON(
    float waterLevel,
    float pressure,
    float flowRate,
    float acoustic)
{
    String json = "{";

    json += "\"device\":\"";
    json += DEVICE_NAME;
    json += "\",";

    json += "\"waterLevel\":";
    json += String(waterLevel, 2);
    json += ",";

    json += "\"pressure\":";
    json += String(pressure, 2);
    json += ",";

    json += "\"flowRate\":";
    json += String(flowRate, 2);
    json += ",";

    json += "\"acoustic\":";
    json += String(acoustic, 2);

    json += "}";

    return json;
}