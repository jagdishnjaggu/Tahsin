#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// DHT config
#define DHTTYPE DHT11
#define DHTPIN1 12
#define DHTPIN2 14
#define DHTPIN3 27
#define DHTPIN4 33

DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);
DHT dht3(DHTPIN3, DHTTYPE);
DHT dht4(DHTPIN4, DHTTYPE);

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Wi-Fi credentials
const char* ssid = "Airtel_MillStory_Office";
const char* password = "MS@airtel2025";

// Firebase config
const char* firebaseHost = "https://mill-live-voltage-default-rtdb.asia-southeast1.firebasedatabase.app/";
const char* firebaseAuth = "rGankdIGsZg4XqWCpF7wJPbJtPOHByxi4vsktQwC";

void setup() {
  Serial.begin(115200);

  dht1.begin();
  dht2.begin();
  dht3.begin();
  dht4.begin();

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Connecting WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connected");
  delay(1000);
  lcd.clear();
}

void loop() {
  static unsigned long lastUpdate = 0;
  unsigned long now = millis();

  if (now - lastUpdate >= 5000) {
    lastUpdate = now;

    float t1 = dht1.readTemperature();
    float h1 = dht1.readHumidity();
    float t2 = dht2.readTemperature();
    float h2 = dht2.readHumidity();
    float t3 = dht3.readTemperature();
    float h3 = dht3.readHumidity();
    float t4 = dht4.readTemperature();
    float h4 = dht4.readHumidity();

    // Replace NaN with fallback values
    if (isnan(t1)) t1 = 20; if (isnan(h1)) h1 = 50;
    if (isnan(t2)) t2 = 20; if (isnan(h2)) h2 = 50;
    if (isnan(t3)) t3 = 20; if (isnan(h3)) h3 = 50;
    if (isnan(t4)) t4 = 20; if (isnan(h4)) h4 = 50;

    float avgTemp = (t1 + t2 + t3 + t4) / 4.0;
    float avgHum  = (h1 + h2 + h3 + h4) / 4.0;

    // Show on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("T:");
    lcd.print(avgTemp, 1);
    lcd.print("C H:");
    lcd.print(avgHum, 1);
    lcd.print("%");

    Serial.printf("Temp: %.1f C, Hum: %.1f %%\n", avgTemp, avgHum);

    // Upload to Firebase
    sendToFirebase(avgTemp, avgHum);
  }
}

void sendToFirebase(float temp, float hum) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(firebaseHost) + "/dht_avg.json?auth=" + firebaseAuth;
    String payload = "{\"temperature\":" + String(temp, 1) +
                     ",\"humidity\":" + String(hum, 1) + "}";

    http.begin(url);
    http.addHeader("Content-Type", "application/json");
    int response = http.PUT(payload);

    Serial.print("Firebase status: ");
    Serial.println(response);

    http.end();
  } else {
    Serial.println("WiFi not connected!");
  }
}
