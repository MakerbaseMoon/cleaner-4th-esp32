#include <WiFi.h>
#include <ESPmDNS.h>

#include "components/setting.h"

IPAddress AP_local_ip(192, 168, 4, 1);
IPAddress AP_gateway (192, 168, 4, 1);
IPAddress AP_subnet(255, 255, 255, 0);

void WiFiEvent(WiFiEvent_t event);

void setup_wifi(Network_conf *network_conf) {
    ESP_LOGI("WiFi", "Setup WiFi.");

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
    ESP_LOGI("WiFi", "Event: %d", event);

    switch (event) {
        case ARDUINO_EVENT_WIFI_STA_GOT_IP:
            ESP_LOGI("WiFi", "STA IP: %s", WiFi.localIP().toString().c_str());
            break;

        case ARDUINO_EVENT_WIFI_AP_START:
            ESP_LOGI("WiFi", "AP IP: %s", WiFi.softAPIP().toString().c_str());
            break;

        default: 
            break;
    }}