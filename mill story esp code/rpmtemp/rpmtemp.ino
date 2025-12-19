#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// ----- Pins -----
#define HALL1_PIN 25
#define HALL2_PIN 26
#define ONE_WIRE_BUS 32  // DS18B20

// ----- Variables -----
volatile int pulseCount1 = 0;
volatile int pulseCount2 = 0;
unsigned long lastUpdateMillis = 0;
int rpm1 = 0, rpm2 = 0;
float temp1 = 0.0, temp2 = 0.0;

// ----- Sensor Setup -----
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress sensor1, sensor2;

// ----- LCD -----
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ----- Interrupts -----
void IRAM_ATTR onPulse1() { pulseCount1++; }
void IRAM_ATTR onPulse2() { pulseCount2++; }

void setup() {
  Serial.begin(115200);

  pinMode(HALL1_PIN, INPUT_PULLUP);
  pinMode(HALL2_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(HALL1_PIN), onPulse1, FALLING);
  attachInterrupt(digitalPinToInterrupt(HALL2_PIN), onPulse2, FALLING);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
  
  sensors.begin();
  if (sensors.getDeviceCount() < 2) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp Sensor < 2");
    while (1);
  }

  sensors.getAddress(sensor1, 0);
  sensors.getAddress(sensor2, 1);

  delay(1000);
  lcd.clear();
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastUpdateMillis >= 1000) {
    lastUpdateMillis = currentMillis;

    // RPM
    rpm1 = pulseCount1 * 60;
    rpm2 = pulseCount2 * 60;
    pulseCount1 = 0;
    pulseCount2 = 0;

    // Temperature
    sensors.requestTemperatures();
    temp1 = sensors.getTempC(sensor1);
    temp2 = sensors.getTempC(sensor2);

    // Debug
    Serial.printf("T1:%.1f T2:%.1f | R1:%d R2:%d\n", temp1, temp2, rpm1, rpm2);

    // Format Strings to fixed width
    char row1[17];
    char row2[17];
    snprintf(row1, sizeof(row1), "T1:%4.1f | T2:%4.1f", temp1, temp2);
    snprintf(row2, sizeof(row2), "R1:%3d  | R2:%3d ", rpm1, rpm2);

    // Display
    lcd.setCursor(0, 0);
    lcd.print(row1);
    lcd.setCursor(0, 1);
    lcd.print(row2);
  }
}
