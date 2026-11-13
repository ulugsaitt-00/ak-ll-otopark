#include "Barrier.h"
#include "config.h"

void Barrier::begin(uint8_t servoPin) {
    servo_.setPeriodHertz(SERVO_PWM_FREQ_HZ);
    servo_.attach(servoPin, SERVO_MIN_PULSE_US, SERVO_MAX_PULSE_US);
    moveTo(BARRIER_CLOSED_ANGLE);   // Sistem acilir acilmaz kapali
    isOpen_ = false;
}

bool Barrier::open(unsigned long now) {
    if (isOpen_) return false;
    moveTo(BARRIER_OPEN_ANGLE);
    isOpen_ = true;
    openedAtMs_ = now;
    return true;
}

void Barrier::update(unsigned long now) {
    if (isOpen_ && now - openedAtMs_ >= BARRIER_OPEN_MS) {
        moveTo(BARRIER_CLOSED_ANGLE);
        isOpen_ = false;
    }
}

void Barrier::moveTo(int angle) {
    servo_.write(angle);
}
