#ifndef __CLEANER_SETTING_H__
#define __CLEANER_SETTING_H__

#include <Arduino.h>

#include "header.h"

#include "components/my_network.h"
#include "components/module.h"

/**
 *   0 ~  24 -> SSID
 *  25 ~  49 -> Password
 *  50 ~  74 -> AP SSID
 *  75 ~  99 -> AP Password
 * 100 ~ 124 -> ESP32 MDNS Name
 * 125 ~ 149 -> Pinout 
 *    125 -> Battery
 *    126-7 -> Battery MAX (2 Bytes)
 *    128-9 -> Battery MIN (2 Bytes)
 * 
 *    130 -> Fan (IRF520)
 * 
 *    131 -> A01 (MX1584)
 *    132 -> A02 (MX1584)
 *    133 -> B01 (MX1584)
 *    134 -> B02 (MX1584)
 * 
 *    135 -> A01 PWM (MX1584)
 *    136 -> A02 PWM (MX1584)
 *    137 -> B01 PWM (MX1584)
 *    138 -> B02 PWM (MX1584)
 * 
 * 150 ~ 174 -> EEPROM (4 is true, other is update) 
 */

#define EEPROM_MAX_LEN          25

#define EEPROM_SSID_ADDRESS        0
#define EEPROM_PASSWD_ADDRESS     25

#define EEPROM_AP_SSID_ADDRESS    50
#define EEPROM_AP_PASSWD_ADDRESS  75

#define EEPROM_MDNS_ADDRESS      100

#define EEPROM_BATTERY_PIN     125
#define EEPROM_BATTERY_MAX     126
#define EEPROM_BATTERY_MIN     128

#define EEPROM_FAN_PIN         130

#define EEPROM_MX1584_A01_PIN  131
#define EEPROM_MX1584_A02_PIN  132
#define EEPROM_MX1584_B01_PIN  133
#define EEPROM_MX1584_B02_PIN  134

#define EEPROM_MX1584_A01_PWM  135
#define EEPROM_MX1584_A02_PWM  136
#define EEPROM_MX1584_B01_PWM  137
#define EEPROM_MX1584_B02_PWM  138

#define EEPROM_CHECK_START     150
#define EEPROM_CHECK_END       174
#define EEPROM_CHECK_NUM       10

// my_eeprom.cpp
void setup_eeprom    (Cleaner_module_conf *cleaner_conf, Network_conf *network_conf);
void get_network_conf(Network_conf *network_conf);
void get_module_conf (Cleaner_module_conf *cleaner_conf);

void set_STA_WiFi(const char* ssid, const char* passwd);
void set_AP_WiFi (const char* ssid, const char* passwd) ;

void set_mDNS_WiFi(const char* mdns);

void set_module(Cleaner_module_conf *cleaner_conf);

void set_default_eeprom();
void clean_all_eeprom();

// nvs.cpp
void setup_data();

#endif