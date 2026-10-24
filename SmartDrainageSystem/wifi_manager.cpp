#include <WiFi.h>
#include "config.h"
#include "wifi_manager.h"

void connectWiFi()
{
    Serial.println();
    Serial.println("==========================");
    Serial.println("Connecting to WiFi");
    Serial.println("==========================");

    Serial.print("SSID: ");
    Serial.println(WIFI_SSID);

    Serial.print("Password Length: ");
    Serial.println(strlen(WIFI_PASSWORD));

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    int attempts = 0;

    while (WiFi.status() != WL_CONNECTED && attempts < 20)
    {
        Serial.print(".");

        Serial.print(" Status=");
        Serial.println(WiFi.status());

        delay(500);
        attempts++;
    }

    Serial.println();

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("WiFi Connected Successfully!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
    }
    else
    {
        Serial.println("WiFi Connection Failed!");
        Serial.print("Final Status: ");
        Serial.println(WiFi.status());
    }
}

bool isWiFiConnected()
{
    return WiFi.status() == WL_CONNECTED;
}