#pragma once
#include <Arduino.h>
#include "UltrasonicSensor.h"
#include "Led.h"

// ParkingSpot: tek bir park yeri. Sensoru periyodik okur, 3 ardisik ayni okumayla
// dolu/bos durumunu degistirir, yesil/kirmizi LED'i surer ve doluluk istatistigini tutar.
class ParkingSpot {
public:
    void begin(uint8_t number, uint8_t trigPin, uint8_t echoPin,
               uint8_t greenLedPin, uint8_t redLedPin);

    // Durum degistiyse true doner
    bool update(unsigned long now);

    bool isOccupied() const { return occupied_; }
    uint8_t number() const { return number_; }
    float lastDistanceCm() const { return lastDistanceCm_; }

    unsigned long occupiedCount() const { return occupiedCount_; }
    // O an dolu olan yerin suresi de dahil
    unsigned long totalOccupiedSeconds(unsigned long now) const;

private:
    void applyState(bool occupied, unsigned long now);
    void refreshLeds();

    UltrasonicSensor sensor_;
    Led greenLed_;
    Led redLed_;

    uint8_t number_ = 0;
    bool occupied_ = false;
    bool candidateState_ = false;
    uint8_t sameReadingCount_ = 0;
    unsigned long lastReadMs_ = 0;
    float lastDistanceCm_ = NAN;

    unsigned long occupiedCount_ = 0;
    unsigned long totalOccupiedMs_ = 0;
    unsigned long occupiedSinceMs_ = 0;
};
