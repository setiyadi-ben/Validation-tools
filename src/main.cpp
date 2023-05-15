#include <Arduino.h>
#include <Wire.h>
#include <TCA9548.h>
#include <BH1750.h>
#include <LiquidCrystal_I2C.h>
// Create an instance of the LCD
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Create an instance of the TCA9548A
TCA9548 multiplexer(0x70); 

// Create instances of the BH1750 sensors
BH1750 sensor1, sensor2;

void setup() {
  Wire.begin();  // Initialize the I2C bus
  multiplexer.begin();  // Initialize the PCA9548A

  // Connect the BH1750 sensors to the PCA9548A
  int TCA9548_CH6 = 6; // Jalur BH1750 kotak
  sensor1.begin(&multiplexer, TCA9548_CH6);
  int TCA9548_CH7 = 7; // Jalur BH1750 bulat
  sensor2.begin(&multiplexer, TCA9548_CH7);
}

void loop ()
{



}