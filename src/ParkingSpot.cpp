#include "ParkingSpot.h"
#include "config.h"

void ParkingSpot::begin(uint8_t number, uint8_t trigPin, uint8_t echoPin,
                        uint8_t greenLedPin, uint8_t redLedPin) {
    number_ = number;
    sensor_.begin(trigPin, echoPin);
    greenLed_.begin(greenLedPin);
    redLed_.begin(redLedPin);
    occupied_ = false;
    refreshLeds();
}

bool ParkingSpot::update(unsigned long now) {
    if (now - lastReadMs_ < SENSOR_READ_INTERVAL_MS) return false;
    lastReadMs_ = now;

    lastDistanceCm_ = sensor_.readDistanceCm();
    bool readingOccupied = lastDistanceCm_ < OCCUPIED_DISTANCE_CM;

    // Titreme onleme: ayni sonuc arka arkaya STABLE_READINGS_REQUIRED kez gelmeli
    if (readingOccupied == candidateState_) {
        if (sameReadingCount_ < STABLE_READINGS_REQUIRED) sameReadingCount_++;
    } else {
        candidateState_ = readingOccupied;
        sameReadingCount_ = 1;
    }

    if (sameReadingCount_ >= STABLE_READINGS_REQUIRED && candidateState_ != occupied_) {
        applyState(candidateState_, now);
        return true;
    }
    return false;
}

void ParkingSpot::applyState(bool occupied, unsigned long now) {
    if (occupied) {
        occupiedCount_++;
        occupiedSinceMs_ = now;
    } else {
        totalOccupiedMs_ += now - occupiedSinceMs_;
    }
    occupied_ = occupied;
    refreshLeds();
}

void ParkingSpot::refreshLeds() {
    // Once sondur, sonra yak: iki LED hicbir an ayni anda yanmaz
    if (occupied_) {
        greenLed_.off();
        redLed_.on();
    } else {
        redLed_.off();
        greenLed_.on();
    }
}

unsigned long ParkingSpot::totalOccupiedSeconds(unsigned long now) const {
    unsigned long totalMs = totalOccupiedMs_;
    if (occupied_) totalMs += now - occupiedSinceMs_;
    return totalMs / MS_PER_SECOND;
}
