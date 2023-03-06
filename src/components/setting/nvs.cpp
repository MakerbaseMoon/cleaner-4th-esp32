#include <Preferences.h>

#include "components/setting.h"

Preferences cleanerData;

void setup_data(Cleaner_module_conf *cleaner_conf, Network_conf *network_conf) {
    if( !cleanerData.begin("cleaner", false) ) {
        Serial.printf("cleanerData begin Error\n");
        while(1);
    }

    // Allocate memory for network configuration parameters if not already done.
    if(*(network_conf->sta_conf.ssid) == NULL) {
        // allocate memory for the network_conf->sta_conf.ssid
        *(network_conf->sta_conf.ssid) = (char*) malloc( sizeof(char) * EEPROM_MAX_LEN );
    }

    if(*(network_conf->sta_conf.passwd) == NULL) {
        // allocate memory for the network_conf->sta_conf.passwd
        *(network_conf->sta_conf.passwd) = (char*) malloc( sizeof(char) * EEPROM_MAX_LEN );
    }

    if(*(network_conf->ap_conf.ssid) == NULL) {
        // allocate memory for the network_conf->ap_conf.ssid
        *(network_conf->ap_conf.ssid) = (char*) malloc( sizeof(char) * EEPROM_MAX_LEN );
    }

    if(*(network_conf->ap_conf.passwd) == NULL) {
        // allocate memory for the network_conf->ap_conf.passwd
        *(network_conf->ap_conf.passwd) = (char*) malloc( sizeof(char) * EEPROM_MAX_LEN );
    }

    if(*(network_conf->mdns) == NULL) {
        // allocate memory for the network_conf->mdns
        *(network_conf->mdns) = (char*) malloc( sizeof(char) * EEPROM_MAX_LEN );
    }

    strcpy(*(network_conf->sta_conf.ssid), cleanerData.getString("ssid", CLEANER_DEFAULT_STA_SSID).c_str());
    strcpy(*(network_conf->sta_conf.passwd), cleanerData.getString("passwd", CLEANER_DEFAULT_STA_PASSWD).c_str());

    strcpy(*(network_conf->ap_conf.ssid), cleanerData.getString("ap_ssid", CLEANER_DEFAULT_AP_SSID).c_str());
    strcpy(*(network_conf->ap_conf.passwd), cleanerData.getString("ap_passwd", CLEANER_DEFAULT_AP_PASSWD).c_str());

    strcpy(*(network_conf->mdns), cleanerData.getString("mDNS", CLEANER_DEFAULT_MDNS).c_str());

    cleaner_conf->battery_conf.pin = cleanerData.getUInt("battery_pin", CLEANER_DEFAULT_BATTERY);
    cleaner_conf->battery_conf.min = cleanerData.getUInt("battery_max", CLEANER_DEFAULT_BATTERY_MAX_VALUE);
    cleaner_conf->battery_conf.max = cleanerData.getUInt("battery_min", CLEANER_DEFAULT_BATTERY_MIN_VALUE);

    cleaner_conf->IRF520_pin = cleanerData.getUInt("fan_pin", CLEANER_DEFAULT_FAN);

    cleaner_conf->mx1584_pinout_conf.pin_A01 = cleanerData.getUInt("A01_pin", CLEANER_DEFAULT_MOTOR_A01);
    cleaner_conf->mx1584_pinout_conf.pin_A02 = cleanerData.getUInt("A02_pin", CLEANER_DEFAULT_MOTOR_A02);
    cleaner_conf->mx1584_pinout_conf.pin_B01 = cleanerData.getUInt("B01_pin", CLEANER_DEFAULT_MOTOR_B01);
    cleaner_conf->mx1584_pinout_conf.pin_B02 = cleanerData.getUInt("B02_pin", CLEANER_DEFAULT_MOTOR_B02);
    
    cleaner_conf->mx1584_pwm_conf.channel_A01 = cleanerData.getUInt("A01_pwm", CLEANER_DEFAULT_MOTOR_PWM);
    cleaner_conf->mx1584_pwm_conf.channel_A02 = cleanerData.getUInt("A02_pwm", CLEANER_DEFAULT_MOTOR_PWM);
    cleaner_conf->mx1584_pwm_conf.channel_B01 = cleanerData.getUInt("B01_pwm", CLEANER_DEFAULT_MOTOR_PWM);
    cleaner_conf->mx1584_pwm_conf.channel_B02 = cleanerData.getUInt("B02_pwm", CLEANER_DEFAULT_MOTOR_PWM);
    
    cleanerData.end();
}
