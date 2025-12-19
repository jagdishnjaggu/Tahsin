// Simple ESP32 Blink Code

#define LED_BUILTIN 2 // Most ESP32 boards have built-in LED on GPIO2

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH); // Turn LED ON
  delay(500); // Wait 500ms
  digitalWrite(LED_BUILTIN, LOW); // Turn LED OFF
  delay(500); // Wait 500ms
}
