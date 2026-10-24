#ifndef CONFIG_H
#define CONFIG_H

//========================
// Wi-Fi Credentials
//========================

constexpr const char* WIFI_SSID = "DESKTOP-SRVG6F9 6943";
constexpr const char* WIFI_PASSWORD = "n|2733T1";

//========================
// Device Information
//========================

#define DEVICE_NAME "SmartDrainageNode01"

//========================
// Server Information
//========================

#define SERVER_IP "192.168.1.100"
#define SERVER_PORT 8000

//========================
// Sensor Pins
//========================

#define TRIG_PIN 5
#define ECHO_PIN 18

#define PRESSURE_PIN 34
#define ACOUSTIC_PIN 35
#define FLOW_SENSOR_PIN 27

//========================
// Actuator Pins
//========================

#define SERVO_PIN 14
#define FAN_RELAY_PIN 26
#define PUMP_RELAY_PIN 25
#define STATUS_LED 2

#endif