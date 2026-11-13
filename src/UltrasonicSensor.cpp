#include "UltrasonicSensor.h"
#include "config.h"

void UltrasonicSensor::begin(uint8_t trigPin, uint8_t echoPin) {
    trigPin_ = trigPin;
    echoPin_ = echoPin;
    pinMode(trigPin_, OUTPUT);
    pinMode(echoPin_, INPUT);
    digitalWrite(trigPin_, LOW);
}

float UltrasonicSensor::readDistanceCm() {
    // HC-SR04 tetikleme darbesi (izin verilen tek istisna: delayMicroseconds)
    digitalWrite(trigPin_, LOW);
    delayMicroseconds(TRIG_SETTLE_US);
    digitalWrite(trigPin_, HIGH);
    delayMicroseconds(TRIG_PULSE_US);
    digitalWrite(trigPin_, LOW);

    unsigned long echoDurationUs = pulseIn(echoPin_, HIGH, ECHO_TIMEOUT_US);
    if (echoDurationUs == 0) {
        return NO_ECHO_DISTANCE_CM;
    }
    return echoDurationUs * CM_PER_US_ONE_WAY;
}
