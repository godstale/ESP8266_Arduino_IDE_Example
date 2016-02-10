/*
 ESP8266 Blink by Simon Peter
 Blink the blue LED on the ESP-01 module
 This example code is in the public domain
 
 Modified by HardCopyWorld.com
*/

int LED = 14;    // Use D5, GPIO14

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);     // Initialize the LED pin as an output
}

// the loop function runs over and over again forever
void loop() {
  int analog = analogRead(A0);
  Serial.println(analog);
  analogWrite(LED, analog/4);
  delay(100);  // Wait for a while
}
