#pragma once
#include <Arduino.h>

// DebouncedButton: INPUT_PULLUP butonu yazilimsal debounce ile okur.
// Her fiziksel basista wasPressed() yalnizca bir kez true doner.
class DebouncedButton {
public:
    void begin(uint8_t pin);
    bool wasPressed(unsigned long now);

private:
    uint8_t pin_ = 0;
    int stableLevel_ = HIGH;
    int lastRawLevel_ = HIGH;
    unsigned long lastChangeMs_ = 0;
};
