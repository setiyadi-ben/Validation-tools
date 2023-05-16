## Validation Tool
### What is it for?
Membantu memvalidasi nilai dari pembacaan _sensor reading_ BH1750 untuk dibandingkan dengan alat ukur _light meter_ yang dijual di pasaran.

### Why is it needed?
Standar pembacaan nilai _sensor reading_ yang berbeda menghasilkan perbedaan simpangan nilai yang tidak berderet membuat selisih antara _sensor_ BH1750 dan _light meter_ menjadi tidak beraturan yang mengakibatkan tidak dapat di kalibrasikan. Oleh karena itu dibuat alat validasi ini untuk mengetahui seberapa besar simpangan nilai pada tempat dengan intensitas cahaya tertentu (Saya). 

Pembacaan nilai sensor yang berbeda dengan standar yang beragam menghasilkan perbedaan simpangan nilai yang tidak konsisten. Hal ini mengakibatkan ketidakberaturan selisih antara _sensor_ BH1750 dan _light meter_ sehingga sulit untuk dilakukan kalibrasi. Untuk mengatasi masalah tersebut, dibuatlah alat validasi ini dengan tujuan untuk mengukur seberapa besar simpangan nilai pada tempat dengan intensitas cahaya tertentu (Improved by ChatGPT). 

### What sensors and measurement tools?
- BH1750 - [datasheet in PDF](datasheet/bh1750fvi-e-186247.pdf)
- BH1750FVI - [datasheet in PDF](datasheet/bh1750fvi-e-186247.pdf)
- UNI-T UT383 - [datasheet in PDF](datasheet/UT383%20UT383BT.pdf)
- SMART SENSOR AS803 - [datasheet in PDF](datasheet/pdfcoffee.com_smart-sensor-as803-digital-lux-meter-pdf-4-pdf-free.pdf)

### The thingy

[photo]

### Code
> **Note**: Make sure you have the latest versions of the TCA9548 and BH1750 libraries installed. Generated and improved by ChatGPT at 15 May 2023.

```cpp
#include <Arduino.h>
#include <Wire.h>
#include <TCA9548.h> //https://github.com/RobTillaart/TCA9548
#include <BH1750.h>
#include <LiquidCrystal_I2C.h>
// Create an instance of the LCD
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Create an instance of the TCA9548A
TCA9548 multiplexer(0x70); 
#define TCA9548_CH6 6 // BH1750 kotak
#define TCA9548_CH7 7 // BH1750 bulat

BH1750 sensor1;
BH1750 sensor2;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  lcd.begin(20, 4);
  lcd.backlight();
  lcd.clear();

  // Initialize the multiplexer
  multiplexer.begin();

  // Enable channels for the sensors
  multiplexer.enableChannel(TCA9548_CH6); // Channel for sensor1
  multiplexer.enableChannel(TCA9548_CH7); // Channel for sensor2

  // Begin the BH1750 sensors
  sensor1.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, 0x23, &Wire);
  sensor2.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, 0x23, &Wire);
}

void loop() {
  // Read light levels from sensor1
  multiplexer.selectChannel(TCA9548_CH6);
  float lux1 = sensor1.readLightLevel();

  // Read light levels from sensor2
  multiplexer.selectChannel(TCA9548_CH7);
  float lux2 = sensor2.readLightLevel();

  // Print the results
  Serial.print("Sensor 1: ");
  Serial.print(lux1);
  Serial.print(" lux");

  Serial.print("Sensor 2: ");
  Serial.print(lux2);
  Serial.print(" lux");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("BH1750 Sensor Read");

  lcd.setCursor(0, 2);
  lcd.print("Lux-01 : ");
  lcd.print(lux1);
  lcd.print(" lx");

  lcd.setCursor(0, 3);
  lcd.print("Lux-02 : ");
  lcd.print(lux2);
  lcd.print(" lx");

  delay(1000);
}