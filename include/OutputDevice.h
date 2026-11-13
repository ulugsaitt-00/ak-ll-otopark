#pragma once
#include <Arduino.h>

// OutputDevice: LED, buzzer gibi tek pinle surulen cikis cihazlari icin soyut temel sinif.
// Alt siniflar on() ve off() davranisini kendileri tanimlar.
class OutputDevice {
public:
    virtual ~OutputDevice() {}

    virtual void begin(uint8_t pin) {
        pin_ = pin;
        pinMode(pin_, OUTPUT);
        off();
    }

    virtual void on() = 0;
    virtual void off() = 0;

    bool isOn() const { return isOn_; }

protected:
    uint8_t pin_ = 0;
    bool isOn_ = false;
};
