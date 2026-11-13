#include "ParkingLot.h"

void ParkingLot::begin() {
    Serial.begin(SERIAL_BAUD);

    for (uint8_t i = 0; i < SPOT_COUNT; i++) {
        spots_[i].begin(FIRST_SPOT_NUMBER + i, SPOT_TRIG_PINS[i], SPOT_ECHO_PINS[i],
                        SPOT_GREEN_LED_PINS[i], SPOT_RED_LED_PINS[i]);
    }

    entryBarrier_.begin(ENTRY_SERVO_PIN);
    exitBarrier_.begin(EXIT_SERVO_PIN);
    entryButton_.begin(ENTRY_BUTTON_PIN);
    exitButton_.begin(EXIT_BUTTON_PIN);
    buzzer_.begin(BUZZER_PIN);
    display_.begin();
    refreshDisplay();

    Serial.println("Akilli otopark hazir. Istatistik icin seri monitore 's' yazin.");
}

void ParkingLot::update() {
    unsigned long now = millis();

    updateSpots(now);

    if (entryButton_.wasPressed(now)) handleEntryRequest(now);
    if (exitButton_.wasPressed(now)) handleExitRequest(now);

    entryBarrier_.update(now);
    exitBarrier_.update(now);
    buzzer_.update(now);
    display_.update(now);
    handleSerialCommands(now);
}

void ParkingLot::updateSpots(unsigned long now) {
    bool anyChanged = false;
    for (uint8_t i = 0; i < SPOT_COUNT; i++) {
        if (spots_[i].update(now)) {
            anyChanged = true;
            logSpotChange(spots_[i]);
            if (!spots_[i].isOccupied()) printStatistics(now);  // Arac cikinca istatistik
        }
    }
    if (anyChanged) refreshDisplay();
}

void ParkingLot::handleEntryRequest(unsigned long now) {
    if (entryBarrier_.isOpen()) return;   // Acikken gelen basislar yok sayilir

    if (freeSpotCount() > 0) {
        entryBarrier_.open(now);
        Serial.println("Giris bariyeri acildi");
    } else {
        buzzer_.beep(FULL_WARNING_BEEP_COUNT, now);
        display_.showTemporaryMessage("OTOPARK DOLU", now, FULL_MESSAGE_MS);
        Serial.println("Giris reddedildi: OTOPARK DOLU");
    }
}

void ParkingLot::handleExitRequest(unsigned long now) {
    // Cikis bariyeri doluluga bakmadan acilir
    if (exitBarrier_.open(now)) Serial.println("Cikis bariyeri acildi");
}

void ParkingLot::handleSerialCommands(unsigned long now) {
    while (Serial.available() > 0) {
        char command = (char)Serial.read();
        if (tolower(command) == STATS_COMMAND_CHAR) printStatistics(now);
    }
}

void ParkingLot::refreshDisplay() {
    String topLine = "BOS YER: " + String(freeSpotCount()) + "/" + String(SPOT_COUNT);
    String bottomLine;
    for (uint8_t i = 0; i < SPOT_COUNT; i++) {
        if (i > 0) bottomLine += " ";
        bottomLine += "P" + String(spots_[i].number()) + ":" + (spots_[i].isOccupied() ? "D" : "B");
    }
    display_.showStatus(topLine, bottomLine);
}

void ParkingLot::logSpotChange(const ParkingSpot& spot) {
    const char* oldState = spot.isOccupied() ? "BOS" : "DOLU";
    const char* newState = spot.isOccupied() ? "DOLU" : "BOS";
    Serial.printf("P%u: %s -> %s (%.0f cm) | Bos yer: %u/%u\n",
                  spot.number(), oldState, newState, spot.lastDistanceCm(),
                  freeSpotCount(), SPOT_COUNT);
}

void ParkingLot::printStatistics(unsigned long now) {
    String line = "Istatistik -> ";
    for (uint8_t i = 0; i < SPOT_COUNT; i++) {
        if (i > 0) line += " | ";
        line += "P" + String(spots_[i].number()) + ": " + String(spots_[i].occupiedCount()) +
                " kez, " + String(spots_[i].totalOccupiedSeconds(now)) + " sn";
    }
    Serial.println(line);
}

uint8_t ParkingLot::freeSpotCount() const {
    uint8_t freeCount = 0;
    for (uint8_t i = 0; i < SPOT_COUNT; i++) {
        if (!spots_[i].isOccupied()) freeCount++;
    }
    return freeCount;
}
