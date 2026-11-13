#pragma once
#include "OutputDevice.h"

// Buzzer: LEDC PWM ile ses ureten buzzer. OutputDevice'tan turer.
// beep() ile istenen sayida kisa bip, delay() kullanmadan update() icinde calinir.
class Buzzer : public OutputDevice {
public:
    void begin(uint8_t pin) override;
    void on() override;
    void off() override;

    void beep(uint8_t count, unsigned long now);
    void update(unsigned long now);

private:
    uint8_t remainingBeeps_ = 0;
    unsigned long lastToggleMs_ = 0;
};
