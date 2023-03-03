#include <WiFi.h>
#include <ESPmDNS.h>

#include "components/setting.h"

IPAddress AP_local_ip(192, 168, 4, 1);
IPAddress AP_gateway (192, 168, 4, 1);
IPAddress AP_subnet(255, 255, 255, 0);

void WiFiEvent(WiFiEvent_t event);

void setup_wifi(Network_conf *network_conf) {
    WiFi.onEvent(WiFiEvent);
    WiFi.setHostname(CLEANER_DEFAULT_MDNS);
    WiFi.mode(WIFI_AP_STA);

    MDNS.begin(*(network_conf->mdns));

    WiFi.disconnect();
    WiFi.softAPConfig(AP_local_ip, AP_gateway, AP_subnet);
    WiFi.softAP(*(network_conf->ap_conf. ssid), *(network_conf->ap_conf. passwd));
    WiFi.begin (*(network_conf->sta_conf.ssid), *(network_conf->sta_conf.passwd));
}

void WiFiEvent(WiFiEvent_t event){
    Serial.printf("[WiFi-event] event: %d\n", event);

    switch (event) {
        case ARDUINO_EVENT_WIFI_READY: 
            Serial.println("WiFi interface ready");
            break;
        case ARDUINO_EVENT_WIFI_SCAN_DONE:
            Serial.println("Completed scan for access points");
            break;

        case ARDUINO_EVENT_WIFI_STA_START:
            Serial.println("WiFi client started");
            break;
        case ARDUINO_EVENT_WIFI_STA_STOP:
            Serial.println("WiFi clients stopped");
            break;
        case ARDUINO_EVENT_WIFI_STA_CONNECTED:
            Serial.println("Connected to access point");
            break;
        case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
            Serial.println("Disconnected from WiFi access point");
            break;
            
        case ARDUINO_EVENT_WIFI_STA_AUTHMODE_CHANGE:
            Serial.println("Authentication mode of access point has changed");
            break;

        case ARDUINO_EVENT_WIFI_STA_GOT_IP:
            Serial.print("Obtained IP address: ");
            Serial.println(WiFi.localIP());
            break;
        case ARDUINO_EVENT_WIFI_STA_LOST_IP:
            Serial.println("Lost IP address and IP address is reset to 0");
            break;

        case ARDUINO_EVENT_WPS_ER_SUCCESS:
            Serial.println("WiFi Protected Setup (WPS): succeeded in enrollee mode");
            break;
        case ARDUINO_EVENT_WPS_ER_FAILED:
            Serial.println("WiFi Protected Setup (WPS): failed in enrollee mode");
            break;
        case ARDUINO_EVENT_WPS_ER_TIMEOUT:
            Serial.println("WiFi Protected Setup (WPS): timeout in enrollee mode");
            break;
        case ARDUINO_EVENT_WPS_ER_PIN:
            Serial.println("WiFi Protected Setup (WPS): pin code in enrollee mode");
            break;

        case ARDUINO_EVENT_WIFI_AP_START:
            Serial.println("WiFi access point started");
            Serial.println(WiFi.softAPIP());
            break;
        case ARDUINO_EVENT_WIFI_AP_STOP:
            // WiFi access point stopped.
            break;
        default: 
            break;
    }}