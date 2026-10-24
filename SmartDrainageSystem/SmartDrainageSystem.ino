#include "config.h"
#include "wifi_manager.h"
#include "sensors.h"
#include "json_manager.h"
#include "prediction.h"
#include "api_manager.h"
#include "actuator.h"
#include "utilities.h"

void setup()
{
    Serial.begin(115200);
    delay(1000);

    // ==========================================
    // System Information
    // ==========================================

    printSystemInfo();

    Serial.println();
    Serial.println("==============================");
    Serial.println("SMART DRAINAGE SYSTEM");
    Serial.println("==============================");

    // ==========================================
    // Connect Wi-Fi
    // ==========================================

    connectWiFi();

    // ==========================================
    // Initialize Sensors
    // ==========================================

    initializeSensors();

    // ==========================================
    // Initialize API Manager
    // ==========================================

    initializeAPI();

    // ==========================================
    // Initialize Actuators
    // ==========================================

    initializeActuators();

    // ==========================================
    // Memory Information
    // ==========================================

    printMemory();

    Serial.println("==============================");
    Serial.println("SYSTEM INITIALIZATION COMPLETE");
    Serial.println("==============================");
}

void loop()
{
    // ==========================================
    // Wi-Fi Status
    // ==========================================

    if(isWiFiConnected())
    {
        Serial.println("Wi-Fi Status : Connected");
    }
    else
    {
        Serial.println("Wi-Fi Lost");
    }

    // ==========================================
    // Read Sensor Values
    // ==========================================

    float waterLevel = readWaterLevel();
    float pressure = readPressure();
    float flowRate = readFlowRate();
    float acoustic = readAcoustic();

    Serial.println("---------------------------------");

    Serial.print("Water Level : ");
    Serial.print(waterLevel);
    Serial.println(" cm");

    Serial.print("Pressure : ");
    Serial.print(pressure);
    Serial.println(" kPa");

    Serial.print("Flow Rate : ");
    Serial.print(flowRate);
    Serial.println(" L/min");

    Serial.print("Acoustic : ");
    Serial.print(acoustic);
    Serial.println(" dB");

    // ==========================================
    // Create JSON from Sensor Readings
    // ==========================================

    String json = createSensorJSON(
        waterLevel,
        pressure,
        flowRate,
        acoustic
    );

    Serial.println("---------------------------------");
    Serial.println("JSON DATA:");
    Serial.println(json);
    Serial.println("---------------------------------");

    // ==========================================
    // Prediction
    // ==========================================

    String status = predictDrainageStatus(
        waterLevel,
        pressure,
        flowRate,
        acoustic
    );

    Serial.print("Prediction : ");
    Serial.println(status);

    Serial.println("---------------------------------");

    // ==========================================
    // Send JSON Data to FastAPI
    // ==========================================

    bool apiResult = sendSensorData(json);

    if(apiResult)
    {
        Serial.println("API Status : Data Sent Successfully");
    }
    else
    {
        Serial.println("API Status : Data Sending Failed");
    }

    Serial.println("---------------------------------");

    // ==========================================
    // Actuator Control
    // ==========================================

    if(status == "Normal")
    {
        closeVent();
        fanOFF();
        pumpOFF();
        ledOFF();
    }

    else if(status == "Warning")
    {
        closeVent();
        fanOFF();
        pumpOFF();
        ledON();
    }

    else if(status == "Blocked")
    {
        closeVent();
        fanOFF();
        pumpOFF();
        ledON();
    }

    else if(status == "Gas Warning")
    {
        openVent();
        fanON();
        pumpOFF();
        ledON();
    }

    else if(status == "Flood")
    {
        openVent();
        fanOFF();
        pumpON();
        ledON();
    }

    // ==========================================
    // Memory Information
    // ==========================================

    printMemory();

    Serial.println("---------------------------------");

    delay(5000);
}