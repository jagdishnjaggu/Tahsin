#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 (most modules are 0x27 or 0x3F)
// If nothing appears, try 0x3F instead
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init(); // Initialize LCD
  lcd.backlight(); // Turn on backlight

  lcd.setCursor(0, 0); 
  lcd.print("Milling Machine");

  lcd.setCursor(0, 1); 
  lcd.print("Controller Ready");
}

void loop() {
  // Nothing needed here
}
