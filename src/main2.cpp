#include <Arduino.h>
#include <Preferences.h>

#include "components/setting.h"

// #define STA_SSID   STA_SSID
// #define STA_PASSWD STA_PASSWD

// #define AP_SSID   AP_SSID
// #define AP_PASSWD AP_PASSWD

// #define MDNS MDNS

void setup() {
    Serial.begin(115200);
    while(!Serial);
    
#ifdef STA_SSID
    set_STA_WiFi(STA_SSID, STA_PASSWD);
#endif

#ifdef AP_SSID
    set_AP_WiFi(AP_SSID, AP_PASSWD);
#endif

#ifdef MDNS
    set_mDNS_WiFi(MDNS);
#endif
}

void loop() {

}
