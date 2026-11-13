#include "Led.h"

void Led::on() {
    digitalWrite(pin_, HIGH);
    isOn_ = true;
}

void Led::off() {
    digitalWrite(pin_, LOW);
    isOn_ = false;
}
