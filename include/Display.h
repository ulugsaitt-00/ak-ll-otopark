#pragma once
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

// Display: 16x2 I2C LCD. Satirlari sadece icerik degistiginde yazar.
// Gecici mesajlari (OTOPARK DOLU gibi) belirli sure gosterip sonra durum ekranina doner.
class Display {
public:
    Display();
    void begin();
    void showStatus(const String& topLine, const String& bottomLine);
    void showTemporaryMessage(const String& topLine, unsigned long now, unsigned long durationMs);
    void update(unsigned long now);

private:
    void render(const String& topLine, const String& bottomLine);
    void writeLine(uint8_t row, const String& text);

    LiquidCrystal_I2C lcd_;
    String statusTop_;
    String statusBottom_;
    String shownTop_;
    String shownBottom_;
    bool messageActive_ = false;
    unsigned long messageStartMs_ = 0;
    unsigned long messageDurationMs_ = 0;
};
