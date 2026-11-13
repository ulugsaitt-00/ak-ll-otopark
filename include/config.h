#pragma once
#include <Arduino.h>

// ================== Park yerleri ==================
// Yeni park yeri eklemek icin SPOT_COUNT'u artirip dizilere pin eklemek yeterli.
constexpr uint8_t SPOT_COUNT = 3;
constexpr uint8_t SPOT_TRIG_PINS[SPOT_COUNT]      = {5, 18, 32};
constexpr uint8_t SPOT_ECHO_PINS[SPOT_COUNT]      = {34, 35, 39};
constexpr uint8_t SPOT_GREEN_LED_PINS[SPOT_COUNT] = {25, 26, 33};
constexpr uint8_t SPOT_RED_LED_PINS[SPOT_COUNT]   = {13, 14, 27};
constexpr uint8_t FIRST_SPOT_NUMBER = 1;

// ================== Ultrasonik sensor ==================
constexpr float OCCUPIED_DISTANCE_CM = 30.0f;          // Bu mesafenin altinda yer dolu
constexpr unsigned long SENSOR_READ_INTERVAL_MS = 200; // Her yer en az bu siklikta okunur
constexpr uint8_t STABLE_READINGS_REQUIRED = 3;        // Titreme onleme: ardisik ayni okuma sayisi
constexpr unsigned long ECHO_TIMEOUT_US = 30000;
constexpr unsigned int TRIG_SETTLE_US = 2;
constexpr unsigned int TRIG_PULSE_US = 10;
constexpr float CM_PER_US_ONE_WAY = 0.0343f / 2.0f;    // Ses hizi / 2 (gidis-donus)
constexpr float NO_ECHO_DISTANCE_CM = 999.0f;          // Yanki gelmezse kabul edilen mesafe

// ================== Bariyerler (servo) ==================
constexpr uint8_t ENTRY_SERVO_PIN = 19;
constexpr uint8_t EXIT_SERVO_PIN = 23;
constexpr int BARRIER_CLOSED_ANGLE = 0;
constexpr int BARRIER_OPEN_ANGLE = 90;
constexpr unsigned long BARRIER_OPEN_MS = 3000;
constexpr int SERVO_PWM_FREQ_HZ = 50;
constexpr int SERVO_MIN_PULSE_US = 500;
constexpr int SERVO_MAX_PULSE_US = 2400;

// ================== Butonlar ==================
constexpr uint8_t ENTRY_BUTTON_PIN = 16;
constexpr uint8_t EXIT_BUTTON_PIN = 17;
constexpr unsigned long BUTTON_DEBOUNCE_MS = 50;

// ================== Buzzer ==================
constexpr uint8_t BUZZER_PIN = 4;
constexpr uint8_t BUZZER_LEDC_CHANNEL = 7;
constexpr uint8_t BUZZER_LEDC_RESOLUTION_BITS = 8;
constexpr unsigned int BUZZER_FREQ_HZ = 2000;
constexpr unsigned int BUZZER_SILENT_FREQ_HZ = 0;
constexpr unsigned long BEEP_ON_MS = 150;
constexpr unsigned long BEEP_OFF_MS = 150;
constexpr uint8_t FULL_WARNING_BEEP_COUNT = 3;

// ================== LCD (I2C) ==================
constexpr uint8_t LCD_I2C_ADDRESS = 0x27;
constexpr uint8_t LCD_COLUMNS = 16;
constexpr uint8_t LCD_ROWS = 2;
constexpr uint8_t LCD_TOP_ROW = 0;
constexpr uint8_t LCD_BOTTOM_ROW = 1;
constexpr uint8_t LCD_SDA_PIN = 21;
constexpr uint8_t LCD_SCL_PIN = 22;
constexpr unsigned long FULL_MESSAGE_MS = 2000;

// ================== Seri port ==================
constexpr unsigned long SERIAL_BAUD = 115200;
constexpr char STATS_COMMAND_CHAR = 's'; // Seri monitore 's' yazinca istatistik basilir
constexpr unsigned long MS_PER_SECOND = 1000;
