#ifndef __CLEANER_SETTING_H__
#define __CLEANER_SETTING_H__

#include <Arduino.h>

#include "header.h"

#include "components/my_network.h"
#include "components/module.h"

#define CLEANER_PREFERENCES_STRING_MAX_LEN 25

#define CLEANER_PREFERENCES_NAME "cleaner"

#define CLEANER_PREFERENCES_KEY_STA_SSID "0"
#define CLEANER_PREFERENCES_KEY_STA_PASSWD "1"

#define CLEANER_PREFERENCES_KEY_AP_SSID "2"
#define CLEANER_PREFERENCES_KEY_AP_PASSWD "3"

#define CLEANER_PREFERENCES_KEY_MDNS "4"

#define CLEANER_PREFERENCES_KEY_BATTERY_PIN "5"
#define CLEANER_PREFERENCES_KEY_BATTERY_MAX "6"
#define CLEANER_PREFERENCES_KEY_BATTERY_MIN "7"

#define CLEANER_PREFERENCES_KEY_FAN_PIN "8"

#define CLEANER_PREFERENCES_KEY_A01_PIN "9"
#define CLEANER_PREFERENCES_KEY_A02_PIN "a"
#define CLEANER_PREFERENCES_KEY_B01_PIN "b"
#define CLEANER_PREFERENCES_KEY_B02_PIN "c"

#define CLEANER_PREFERENCES_KEY_A01_PWM "d"
#define CLEANER_PREFERENCES_KEY_A02_PWM "e"
#define CLEANER_PREFERENCES_KEY_B01_PWM "f"
#define CLEANER_PREFERENCES_KEY_B02_PWM "g"

// nvs.cpp
void setup_data(Cleaner_module_conf *cleaner_conf, Network_conf *network_conf);
void set_STA_WiFi(const char* ssid, const char* passwd);
void set_AP_WiFi (const char* ssid, const char* passwd) ;

void set_mDNS_WiFi(const char* mdns);

void set_module(Cleaner_module_conf *cleaner_conf);

#endif