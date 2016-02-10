/*
 ESP8266 Blink by Simon Peter
 Blink the blue LED on the ESP-01 module
 This example code is in the public domain

  Modified by HardCopyWorld.com
*/

int LED = 14;    // Use D5, GPIO14

void setup() {
  pinMode(LED, OUTPUT);     // Initialize the LED pin as an output
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED, LOW);   // Turn the LED
  delay(1000);    // Wait for a seconds
  digitalWrite(LED, HIGH);  // Turn the LED
  delay(1000);    // Wait for a seconds
}
