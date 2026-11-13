#include <Arduino.h>
#include "ParkingLot.h"

// Butun is ParkingLot ve icindeki siniflarda doner.
ParkingLot parkingLot;

void setup() {
    parkingLot.begin();
}

void loop() {
    parkingLot.update();
}
