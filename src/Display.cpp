#include "Display.h"
#include <Wire.h>
#include "config.h"

Display::Display() : lcd_(LCD_I2C_ADDRESS, LCD_COLUMNS, LCD_ROWS) {}

void Display::begin() {
    Wire.begin(LCD_SDA_PIN, LCD_SCL_PIN);
    lcd_.init();
    lcd_.backlight();
    lcd_.clear();
}

void Display::showStatus(const String& topLine, const String& bottomLine) {
    statusTop_ = topLine;
    statusBottom_ = bottomLine;
    if (!messageActive_) render(statusTop_, statusBottom_);
    else render(shownTop_, statusBottom_);   // Mesaj surerken alt satir guncel kalsin
}

void Display::showTemporaryMessage(const String& topLine, unsigned long now, unsigned long durationMs) {
    messageActive_ = true;
    messageStartMs_ = now;
    messageDurationMs_ = durationMs;
    render(topLine, statusBottom_);
}

void Display::update(unsigned long now) {
    if (messageActive_ && now - messageStartMs_ >= messageDurationMs_) {
        messageActive_ = false;
        render(statusTop_, statusBottom_);
    }
}

void Display::render(const String& topLine, const String& bottomLine) {
    if (topLine != shownTop_) {
        writeLine(LCD_TOP_ROW, topLine);
        shownTop_ = topLine;
    }
    if (bottomLine != shownBottom_) {
        writeLine(LCD_BOTTOM_ROW, bottomLine);
        shownBottom_ = bottomLine;
    }
}

void Display::writeLine(uint8_t row, const String& text) {
    String padded = text.substring(0, LCD_COLUMNS);
    while (padded.length() < LCD_COLUMNS) padded += ' ';   // Eski yaziyi temizle
    lcd_.setCursor(0, row);
    lcd_.print(padded);
}
