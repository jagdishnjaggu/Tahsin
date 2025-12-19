#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_ADS1X15.h>

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ADS1115 Modules
Adafruit_ADS1115 ads1;  // Address 0x48
Adafruit_ADS1115 ads2;  // Address 0x49

// Relay & Button Pins
#define RELAY_MILL    14
#define RELAY_FEEDER  25
#define START_BUTTON  33
#define STOP_BUTTON   32

// State
volatile bool millRunning = false;
float ct1_current = 0.0;
float ct2_current = 0.0;
float ct3_current = 0.0;

// Task Handles
TaskHandle_t TaskCurrent;
TaskHandle_t TaskButtons;

void setup() {
  Serial.begin(115200);

  // Pins
  pinMode(RELAY_MILL, OUTPUT);
  pinMode(RELAY_FEEDER, OUTPUT);
  pinMode(START_BUTTON, INPUT_PULLUP);
  pinMode(STOP_BUTTON, INPUT_PULLUP);

  digitalWrite(RELAY_MILL, HIGH);    // OFF state
  digitalWrite(RELAY_FEEDER, HIGH);  // OFF state

  // LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Mill Controller");
  delay(1000);
  lcd.clear();

  // ADC Init
  ads1.begin(0x48);
  ads2.begin(0x49);

  // Tasks
  xTaskCreatePinnedToCore(readCurrentTask, "ReadCurrent", 10000, NULL, 1, &TaskCurrent, 0);
  xTaskCreatePinnedToCore(handleButtonsTask, "HandleButtons", 10000, NULL, 1, &TaskButtons, 1);
}

void loop() {
  // Update display
  lcd.setCursor(0, 0);
  lcd.print("I1  I2  I3");

  lcd.setCursor(0, 1);
  lcd.print(ct1_current, 1); lcd.print(" ");
  lcd.print(ct2_current, 1); lcd.print(" ");
  lcd.print(ct3_current, 1);

  delay(500);
}

// ===================== TASK: READ CURRENT =====================

void readCurrentTask(void * parameter) {
  for(;;) {
    ct1_current = readCT(ads1.readADC_Differential_0_1());
    ct2_current = readCT(ads1.readADC_Differential_2_3());
    ct3_current = readCT(ads2.readADC_Differential_0_1());
    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}

float readCT(int16_t raw_adc) {
  float voltage = abs(raw_adc) * 0.0001875;  // ADS1115 step size
  float current = voltage / 0.01;            // SCT-013 scaling
  return current;
}

// ===================== TASK: HANDLE BUTTONS =====================

void handleButtonsTask(void * parameter) {
  for(;;) {
    if (digitalRead(START_BUTTON) == LOW) {
      millRunning = true;
      digitalWrite(RELAY_MILL, LOW);
      digitalWrite(RELAY_FEEDER, LOW);
      delay(300);
    }

    if (digitalRead(STOP_BUTTON) == LOW) {
      millRunning = false;
      digitalWrite(RELAY_MILL, HIGH);
      digitalWrite(RELAY_FEEDER, HIGH);
      delay(300);
    }

    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}
