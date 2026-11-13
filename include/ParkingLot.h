#pragma once
#include <Arduino.h>
#include "config.h"
#include "ParkingSpot.h"
#include "Barrier.h"
#include "Display.h"
#include "Buzzer.h"
#include "DebouncedButton.h"

// ParkingLot: butun otoparki yonetir. Park yerleri dizisini, iki bariyeri, butonlari,
// LCD'yi ve buzzer'i bir arada calistirir; seri monitore kayit ve istatistik yazar.
class ParkingLot {
public:
    void begin();
    void update();

private:
    void updateSpots(unsigned long now);
    void handleEntryRequest(unsigned long now);
    void handleExitRequest(unsigned long now);
    void handleSerialCommands(unsigned long now);
    void refreshDisplay();
    void logSpotChange(const ParkingSpot& spot);
    void printStatistics(unsigned long now);
    uint8_t freeSpotCount() const;

    ParkingSpot spots_[SPOT_COUNT];
    Barrier entryBarrier_;
    Barrier exitBarrier_;
    DebouncedButton entryButton_;
    DebouncedButton exitButton_;
    Display display_;
    Buzzer buzzer_;
};
