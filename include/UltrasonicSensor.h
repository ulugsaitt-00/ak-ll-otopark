#pragma once
#include <Arduino.h>

// UltrasonicSensor: HC-SR04 sensorunu tetikler ve yanki suresinden mesafeyi cm olarak hesaplar.
class UltrasonicSensor {
public:
    void begin(uint8_t trigPin, uint8_t echoPin);
    float readDistanceCm();

private:
    uint8_t trigPin_ = 0;
    uint8_t echoPin_ = 0;
};
