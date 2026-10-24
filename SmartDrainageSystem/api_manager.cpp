// =====================================================
// AI-Based Smart Drainage Monitoring System
// API Manager Source
// ESP32 DevKit V1
// =====================================================

#include "api_manager.h"
#include "config.h"

#include <WiFi.h>
#include <HTTPClient.h>

// =====================================================
// Initialize API
// =====================================================

void initializeAPI()
{
    Serial.println();
    Serial.println("=================================");
    Serial.println("API Manager Initialized");
    Serial.println("=================================");
}

// =====================================================
// Send Sensor JSON to FastAPI
// =====================================================

bool sendSensorData(String jsonData)
{
    // Check Wi-Fi connection
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("Wi-Fi Not Connected!");
        Serial.println("Cannot Send Data To Server.");

        return false;
    }

    HTTPClient http;

    // Build server URL using existing config.h values
    String url = "http://" + String(SERVER_IP) + ":" +
                 String(SERVER_PORT) + "/sensor-data";

    Serial.println();
    Serial.println("=================================");
    Serial.println("Sending Data To FastAPI");
    Serial.println("=================================");

    Serial.print("Server URL : ");
    Serial.println(url);

    // Start HTTP connection
    http.begin(url);

    // Tell server that we are sending JSON
    http.addHeader("Content-Type", "application/json");

    // Send POST request
    int httpResponseCode = http.POST(jsonData);

    // Check response
    if (httpResponseCode > 0)
    {
        Serial.print("HTTP Response Code : ");
        Serial.println(httpResponseCode);

        String response = http.getString();

        Serial.println("Server Response:");
        Serial.println(response);

        http.end();

        return true;
    }
    else
    {
        Serial.print("HTTP Error : ");
        Serial.println(httpResponseCode);

        http.end();

        return false;
    }
}