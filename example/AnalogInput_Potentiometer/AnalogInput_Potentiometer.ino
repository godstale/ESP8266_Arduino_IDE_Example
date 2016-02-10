/*
 ESP8266 Blink by Simon Peter
 Blink the blue LED on the ESP-01 module
 This example code is in the public domain
 
 Modified by HardCopyWorld.com
*/

void setup() {
  Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop() {
  int analog = analogRead(A0);
  Serial.println(analog);
  delay(100);  // Wait for a while
}
