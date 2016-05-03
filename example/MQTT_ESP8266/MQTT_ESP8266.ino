/*
 Basic ESP8266 MQTT example

 This sketch demonstrates the capabilities of the pubsub library in combination
 with the ESP8266 board/library.

 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic" every two seconds
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  - If the first character of the topic "inTopic" is an 1, switch ON the ESP Led,
    else switch it off

 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.

 To install the ESP8266 board, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
  - Select your ESP8266 in "Tools -> Board"

*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//----- OLED display
/////////////////////////////////////////////
// WARNING !!
//
// Connect SDA, SCL to D2(GPIO4), D1(GPIO5)
// if you're using NodeMCU v1.0
// Default OLED reset pin is D8(GPIO15)
//
#define OLED_RESET 15
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif



//----- WiFi settings
const char *ssid = "your_ap_id";
const char *password = "your_ap_password";
const char* mqtt_server = "mqtt_url";
const char* mqtt_topic = "topic";
char* mqtt_message = "Hello world #%ld";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

#define USE_SERIAL Serial




void setup() {
    // Initialize OLED
    display.begin(SSD1306_SWITCHCAPVCC, 0x3c);  // initialize
    display.display();
    
    //USE_SERIAL.begin(921600);
    USE_SERIAL.begin(115200);
    USE_SERIAL.setDebugOutput(true);
    USE_SERIAL.println();

    for(uint8_t t = 3; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    WiFi.begin(ssid, password);

    Serial.print("Connecting to AP");
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    // clear screen
    display.clearDisplay();
    // show IP
    String out = "";
    out += "IP: ";
    out += WiFi.localIP() & 0xff;
    out += ",";
    out += (WiFi.localIP() >> 8) & 0xff;
    out += ",";
    out += (WiFi.localIP() >> 16) & 0xff;
    out += ",";
    out += (WiFi.localIP() >> 24) & 0xff;
    drawText(0, out);

    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);

    randomSeed(analogRead(0));
}


void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();
  
    long now = millis();
    long randNumber = random(0, 15000);
    if (now - lastMsg > 15000 + randNumber) {
        lastMsg = now;
        ++value;
        snprintf (msg, 75, mqtt_message, value);
        Serial.print("Publish message: ");
        Serial.println(msg);
        client.publish(mqtt_topic, msg);
  
        // Show on OLED
        String msgText = "<= ";
        msgText += msg;
        drawText(0, msgText);
    }
}


void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");


    String msgText = "=> ";
    
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
      msgText += (char)payload[i];
    }
    Serial.println();
  
    // Show on OLED
    String topicText = "";
    topicText += topic;
    drawText(1, topicText);

    drawText(2, msgText);
}


void reconnect() {
    // Loop until we're reconnected
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        if (client.connect("ESP8266Client")) {
            Serial.println("connected");
            // Once connected, publish an announcement...
            client.publish(mqtt_topic, "hello world");
            // ... and resubscribe
            client.subscribe(mqtt_topic);
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}


void drawText(int line, String message) {
    display.setTextSize(1);
    display.setTextColor(WHITE);
    if(line == 0) {
        display.fillRect(0, 0, 128, 21, BLACK);
        display.setCursor(2, 1);
    } else if(line == 1) {
        display.fillRect(0, 21, 128, 21, BLACK);
        display.setCursor(2, 22);
    } else {
        display.fillRect(0, 42, 128, 21, BLACK);
        display.setCursor(2, 42);
    }
    display.print(message);
    display.display();
    delay(10);
}

