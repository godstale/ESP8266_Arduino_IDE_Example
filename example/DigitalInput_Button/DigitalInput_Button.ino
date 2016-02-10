/*
 ESP8266 Blink by Simon Peter
 Blink the blue LED on the ESP-01 module
 This example code is in the public domain
 
 Modified by HardCopyWorld.com
*/

int LED = 14;    // Use D5, GPIO14
int BUTTON = 4;    // Use D2, GPIO4

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);     // Initialize the LED pin as an output
  pinMode(BUTTON, INPUT);     // Initialize the BUTTON pin as an input
}

// the loop function runs over and over again forever
void loop() {
  boolean buttonPressed = digitalRead(BUTTON);
  Serial.println(buttonPressed);
  digitalWrite(LED, buttonPressed);
  delay(100);  // Wait for a while
}
