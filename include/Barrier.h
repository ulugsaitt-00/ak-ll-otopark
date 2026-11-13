#pragma once
#include <Arduino.h>
#include <ESP32Servo.h>

// Barrier: servo motorla surulen bariyer. Acildiktan BARRIER_OPEN_MS sonra millis() ile
// kendiliginden kapanir. Giris ve cikis bariyeri bu siniftan iki ayri nesnedir.
class Barrier {
public:
    void begin(uint8_t servoPin);
    // Bariyer zaten aciksa false doner ve hicbir sey yapmaz
    bool open(unsigned long now);
    void update(unsigned long now);
    bool isOpen() const { return isOpen_; }

private:
    void moveTo(int angle);

    Servo servo_;
    bool isOpen_ = false;
    unsigned long openedAtMs_ = 0;
};
