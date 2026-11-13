#include "DebouncedButton.h"
#include "config.h"

void DebouncedButton::begin(uint8_t pin) {
    pin_ = pin;
    pinMode(pin_, INPUT_PULLUP);
    stableLevel_ = digitalRead(pin_);
    lastRawLevel_ = stableLevel_;
}

bool DebouncedButton::wasPressed(unsigned long now) {
    int rawLevel = digitalRead(pin_);
    if (rawLevel != lastRawLevel_) {
        lastRawLevel_ = rawLevel;
        lastChangeMs_ = now;
    }
    if (now - lastChangeMs_ >= BUTTON_DEBOUNCE_MS && rawLevel != stableLevel_) {
        stableLevel_ = rawLevel;
        return stableLevel_ == LOW;   // Pull-up: basili = LOW
    }
    return false;
}
