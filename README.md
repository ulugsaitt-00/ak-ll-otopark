# Akıllı Otopark (ESP32 + PlatformIO + Wokwi)

3 araçlık otopark: HC-SR04 ile doluluk algılama, giriş/çıkış bariyeri (servo), I2C LCD, buzzer ve doluluk istatistiği.

## Devre bağlantı tablosu
| Parça | ESP32 pini | Açıklama |
|---|---|---|
| HC-SR04 P1 / P2 / P3 TRIG | 5 / 18 / 32 | Tetikleme |
| HC-SR04 P1 / P2 / P3 ECHO | 34 / 35 / 39 | Yankı |
| Yeşil LED P1 / P2 / P3 | 25 / 26 / 33 | Yer boş (220 Ω ile GND'ye) |
| Kırmızı LED P1 / P2 / P3 | 13 / 14 / 27 | Yer dolu (220 Ω ile GND'ye) |
| LCD 16x2 I2C (0x27) | SDA 21, SCL 22 | Boş yer sayısı, mesajlar |
| Giriş servo | 19 | Giriş bariyeri (0° kapalı, 90° açık) |
| Çıkış servo | 23 | Çıkış bariyeri |
| Giriş butonu | 16 | INPUT_PULLUP, diğer ucu GND |
| Çıkış butonu | 17 | INPUT_PULLUP, diğer ucu GND |
| Buzzer | 4 | LEDC PWM ile bip |
| Sensör/servo/LCD VCC | 5V | Breadboard + rayı |

Bütün pinler, eşikler ve süreler `include/config.h` içindedir.

## Sınıflar
- **OutputDevice** – LED ve buzzer için soyut temel sınıf (`on()`, `off()`).
- **Led** – OutputDevice'tan türer, dijital pin ile yanar/söner.
- **Buzzer** – OutputDevice'tan türer, `delay()` kullanmadan N kısa bip çalar.
- **UltrasonicSensor** – HC-SR04'ü tetikler, mesafeyi cm olarak verir.
- **ParkingSpot** – Sensör + 2 LED; 200 ms'de bir okur, 3 ardışık aynı okumayla durum değiştirir, doluluk sayısı ve süresini tutar.
- **Barrier** – Servo bariyer; açıldıktan `BARRIER_OPEN_MS` sonra kendi kapanır. Giriş ve çıkış aynı sınıftan iki nesnedir.
- **Display** – I2C LCD; sadece değişen satırı yazar, geçici mesajı (OTOPARK DOLU) 2 sn gösterir.
- **DebouncedButton** – Yazılımsal debounce, her basışta tek olay.
- **ParkingLot** – Hepsini yönetir: `ParkingSpot spots_[SPOT_COUNT]`, iki bariyer, butonlar, LCD, buzzer, seri kayıtlar.

## Çalıştırma
1. VS Code + PlatformIO IDE + Wokwi Simulator eklentilerini kurun.
2. Klasörü açın, `pio run` ile derleyin.
3. `diagram.json` açıkken **F1 → Wokwi: Start Simulator**.
4. Sensörlere tıklayıp mesafeyi değiştirin, butonlara basın.
5. İstatistik: bir yer boşaldığında otomatik yazılır; ayrıca seri monitöre `s` yazarak istendiği an görülebilir.

## Bilinen eksikler
- Park yeri sayısı 4'e çıkarılırsa LCD alt satırı (`P1:B P2:D P3:B P4:B`) 16 karakteri aştığı için kesilir.
- `pulseIn` yankı beklerken en fazla `ECHO_TIMEOUT_US` (30 ms) bloklar.
- Çıkış bariyeri açıkken tekrar basılırsa süre yeniden başlamaz, bariyer zaten açık kalır.
