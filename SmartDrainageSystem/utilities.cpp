// =====================================================
// AI-Based Smart Drainage Monitoring System
// Utilities Source
// ESP32 DevKit V1
// =====================================================

#include "utilities.h"
#include "config.h"

void printSystemInfo()
{
    Serial.println();
    Serial.println("==========================================");
    Serial.println(" AI Smart Drainage Monitoring System");
    Serial.println(" ESP32 DevKit V1");
    Serial.println("==========================================");

    Serial.print("Device Name : ");
    Serial.println(DEVICE_NAME);

    Serial.print("CPU Frequency : ");
    Serial.print(getCpuFrequencyMhz());
    Serial.println(" MHz");

    Serial.print("Flash Size : ");
    Serial.print(ESP.getFlashChipSize() / (1024 * 1024));
    Serial.println(" MB");

    Serial.println("==========================================");
}

void blinkLED(int times, int delayTime)
{
    for(int i = 0; i < times; i++)
    {
        digitalWrite(STATUS_LED, HIGH);
        delay(delayTime);

        digitalWrite(STATUS_LED, LOW);
        delay(delayTime);
    }
}

void restartESP()
{
    Serial.println();
    Serial.println("Restarting ESP32...");
    delay(2000);
    ESP.restart();
}

void printMemory()
{
    Serial.print("Free Heap Memory : ");
    Serial.print(ESP.getFreeHeap());
    Serial.println(" Bytes");
}

void debugPrint(String message)
{
    Serial.print("[DEBUG] ");
    Serial.println(message);
}