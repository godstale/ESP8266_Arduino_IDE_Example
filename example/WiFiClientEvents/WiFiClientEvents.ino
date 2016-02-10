/*
 *  This sketch shows the WiFi event usage
 *
 *  In this example you can receive and process below events.
 *  Refer to ESP8266WiFiType.h
 *  
 typedef enum {
    WIFI_EVENT_STAMODE_CONNECTED = 0,
    WIFI_EVENT_STAMODE_DISCONNECTED,
    WIFI_EVENT_STAMODE_AUTHMODE_CHANGE,
    WIFI_EVENT_STAMODE_GOT_IP,
    WIFI_EVENT_STAMODE_DHCP_TIMEOUT,
    WIFI_EVENT_SOFTAPMODE_STACONNECTED,
    WIFI_EVENT_SOFTAPMODE_STADISCONNECTED,
    WIFI_EVENT_SOFTAPMODE_PROBEREQRECVED,
    WIFI_EVENT_MAX
} WiFiEvent_t;
 * 
 * hardcopyworld.com
 */

#include <ESP8266WiFi.h>

const char *ssid = "your_ssid";
const char *password = "your_pass";


void WiFiEvent(WiFiEvent_t event) {
    Serial.printf("[WiFi-event] event: %d\n", event);

    switch(event) {
        case WIFI_EVENT_STAMODE_GOT_IP:
            Serial.println("WiFi connected");
            Serial.println("IP address: ");
            Serial.println(WiFi.localIP());
            break;
        case WIFI_EVENT_STAMODE_DISCONNECTED:
            Serial.println("WiFi lost connection");
            break;
    }
}

void setup() {
    Serial.begin(115200);

    // delete old config
    WiFi.disconnect(true);

    delay(1000);

    WiFi.onEvent(WiFiEvent);

    WiFi.begin(ssid, password);

    Serial.println();
    Serial.println();
    Serial.println("Wait for WiFi... ");
}


void loop() {
    delay(1000);
}

