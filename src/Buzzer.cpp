#include "Buzzer.h"
#include "config.h"

void Buzzer::begin(uint8_t pin) {
    pin_ = pin;
#if ESP_ARDUINO_VERSION_MAJOR >= 3
    // Arduino-ESP32 3.x: LEDC fonksiyonlari kanal yerine pin ile calisir
    ledcAttachChannel(pin_, BUZZER_FREQ_HZ, BUZZER_LEDC_RESOLUTION_BITS, BUZZER_LEDC_CHANNEL);
#else
    ledcSetup(BUZZER_LEDC_CHANNEL, BUZZER_FREQ_HZ, BUZZER_LEDC_RESOLUTION_BITS);
    ledcAttachPin(pin_, BUZZER_LEDC_CHANNEL);
#endif
    off();
}

void Buzzer::on() {
#if ESP_ARDUINO_VERSION_MAJOR >= 3
    ledcWriteTone(pin_, BUZZER_FREQ_HZ);
#else
    ledcWriteTone(BUZZER_LEDC_CHANNEL, BUZZER_FREQ_HZ);
#endif
    isOn_ = true;
}

void Buzzer::off() {
#if ESP_ARDUINO_VERSION_MAJOR >= 3
    ledcWriteTone(pin_, BUZZER_SILENT_FREQ_HZ);
#else
    ledcWriteTone(BUZZER_LEDC_CHANNEL, BUZZER_SILENT_FREQ_HZ);
#endif
    isOn_ = false;
}

void Buzzer::beep(uint8_t count, unsigned long now) {
    if (count == 0) return;
    remainingBeeps_ = count;
    on();
    lastToggleMs_ = now;
}

void Buzzer::update(unsigned long now) {
    if (remainingBeeps_ == 0) return;

    if (isOn_ && now - lastToggleMs_ >= BEEP_ON_MS) {
        off();
        remainingBeeps_--;
        lastToggleMs_ = now;
    } else if (!isOn_ && now - lastToggleMs_ >= BEEP_OFF_MS) {
        on();
        lastToggleMs_ = now;
    }
}
