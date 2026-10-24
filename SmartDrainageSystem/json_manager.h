#ifndef JSON_MANAGER_H
#define JSON_MANAGER_H

#include <Arduino.h>

String createSensorJSON(
    float waterLevel,
    float pressure,
    float flowRate,
    float acoustic
);

#endif