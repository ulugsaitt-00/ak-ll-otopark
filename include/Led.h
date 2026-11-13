#pragma once
#include "OutputDevice.h"

// Led: dijital pinle yakilip sondurulen basit LED. OutputDevice'tan turer.
class Led : public OutputDevice {
public:
    void on() override;
    void off() override;
};
