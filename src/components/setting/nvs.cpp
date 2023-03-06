#include <Preferences.h>

#include "components/setting.h"

Preferences cleanerData;

void setup_data(Cleaner_module_conf *cleaner_conf, Network_conf *network_conf) {
    if( !cleanerData.begin(CLEANER_PREFERENCES_NAME, false) ) {
        Serial.printf("cleanerData begin Error\n");
        while(1);
    }

    // Allocate memory for network configuration parameters if not already done.
    if(*(network_conf->sta_conf.ssid) == NULL) {
        // allocate memory for the network_conf->sta_conf.ssid
        *(network_conf->sta_conf.ssid) = (char*) malloc( sizeof(char) * CLEANER_PREFERENCES_STRING_MAX_LEN );
    }

    if(*(network_conf->sta_conf.passwd) == NULL) {
        // allocate memory for the network_conf->sta_conf.passwd
        *(network_conf->sta_conf.passwd) = (char*) malloc( sizeof(char) * CLEANER_PREFERENCES_STRING_MAX_LEN );
    }

    if(*(network_conf->ap_conf.ssid) == NULL) {
        // allocate memory for the network_conf->ap_conf.ssid
        *(network_conf->ap_conf.ssid) = (char*) malloc( sizeof(char) * CLEANER_PREFERENCES_STRING_MAX_LEN );
    }

    if(*(network_conf->ap_conf.passwd) == NULL) {
        // allocate memory for the network_conf->ap_conf.passwd
        *(network_conf->ap_conf.passwd) = (char*) malloc( sizeof(char) * CLEANER_PREFERENCES_STRING_MAX_LEN );
    }

    if(*(network_conf->mdns) == NULL) {
        // allocate memory for the network_conf->mdns
        *(network_conf->mdns) = (char*) malloc( sizeof(char) * CLEANER_PREFERENCES_STRING_MAX_LEN );
    }

    strcpy(*(network_conf->sta_conf.ssid), cleanerData.getString(CLEANER_PREFERENCES_KEY_STA_SSID, CLEANER_DEFAULT_STA_SSID).c_str());
    strcpy(*(network_conf->sta_conf.passwd), cleanerData.getString(CLEANER_PREFERENCES_KEY_STA_PASSWD, CLEANER_DEFAULT_STA_PASSWD).c_str());

    strcpy(*(network_conf->ap_conf.ssid), cleanerData.getString(CLEANER_PREFERENCES_KEY_AP_SSID, CLEANER_DEFAULT_AP_SSID).c_str());
    strcpy(*(network_conf->ap_conf.passwd), cleanerData.getString(CLEANER_PREFERENCES_KEY_AP_PASSWD, CLEANER_DEFAULT_AP_PASSWD).c_str());

    strcpy(*(network_conf->mdns), cleanerData.getString(CLEANER_PREFERENCES_KEY_MDNS, CLEANER_DEFAULT_MDNS).c_str());

    cleaner_conf->battery_conf.pin = cleanerData.getUInt(CLEANER_PREFERENCES_KEY_BATTERY_PIN, CLEANER_DEFAULT_BATTERY);
    cleaner_conf->battery_conf.min = cleanerData.getUInt(CLEANER_PREFERENCES_KEY_BATTERY_MAX, CLEANER_DEFAULT_BATTERY_MAX_VALUE);
    cleaner_conf->battery_conf.max = cleanerData.getUInt(CLEANER_PREFERENCES_KEY_BATTERY_MIN, CLEANER_DEFAULT_BATTERY_MIN_VALUE);

    cleaner_conf->IRF520_pin = cleanerData.getUInt(CLEANER_PREFERENCES_KEY_FAN_PIN, CLEANER_DEFAULT_FAN);

    cleaner_conf->mx1584_pinout_conf.pin_A01 = cleanerData.getUInt(CLEANER_PREFERENCES_KEY_A01_PIN, CLEANER_DEFAULT_MOTOR_A01);
    cleaner_conf->mx1584_pinout_conf.pin_A02 = cleanerData.getUInt(CLEANER_PREFERENCES_KEY_A02_PIN, CLEANER_DEFAULT_MOTOR_A02);
    cleaner_conf->mx1584_pinout_conf.pin_B01 = cleanerData.getUInt(CLEANER_PREFERENCES_KEY_B01_PIN, CLEANER_DEFAULT_MOTOR_B01);
    cleaner_conf->mx1584_pinout_conf.pin_B02 = cleanerData.getUInt(CLEANER_PREFERENCES_KEY_B02_PIN, CLEANER_DEFAULT_MOTOR_B02);
    
    cleaner_conf->mx1584_pwm_conf.channel_A01 = cleanerData.getUInt(CLEANER_PREFERENCES_KEY_A01_PWM, CLEANER_DEFAULT_MOTOR_PWM);
    cleaner_conf->mx1584_pwm_conf.channel_A02 = cleanerData.getUInt(CLEANER_PREFERENCES_KEY_A02_PWM, CLEANER_DEFAULT_MOTOR_PWM);
    cleaner_conf->mx1584_pwm_conf.channel_B01 = cleanerData.getUInt(CLEANER_PREFERENCES_KEY_B01_PWM, CLEANER_DEFAULT_MOTOR_PWM);
    cleaner_conf->mx1584_pwm_conf.channel_B02 = cleanerData.getUInt(CLEANER_PREFERENCES_KEY_B02_PWM, CLEANER_DEFAULT_MOTOR_PWM);
    
    // Save the changes to Preferences
    cleanerData.end();
}

/**
 * @brief This function updates the STA (station) mode WiFi network configuration data in Preferences.
 * 
 * @param ssid STA SSID
 * @param passwd STA Password
 */
void set_STA_WiFi(const char* ssid, const char* passwd) {
    cleanerData.begin(CLEANER_PREFERENCES_NAME, false);

    // Write the SSID and password strings to the appropriate Preferences
    cleanerData.putString(CLEANER_PREFERENCES_KEY_STA_SSID,     ssid);
    cleanerData.putString(CLEANER_PREFERENCES_KEY_STA_PASSWD, passwd);

    // Save the changes to Preferences
    cleanerData.end();
}

/**
 * @brief This function updates the AP (access point) mode WiFi network configuration data in Preferences.
 * 
 * @param ssid AP mode SSID
 * @param passwd AP mode Password
 */
void set_AP_WiFi(const char* ssid, const char* passwd) {
    cleanerData.begin(CLEANER_PREFERENCES_NAME, false);

    // Write the SSID and password strings to the appropriate Preferences addresses
    cleanerData.putString(CLEANER_PREFERENCES_KEY_AP_SSID,     ssid);
    cleanerData.putString(CLEANER_PREFERENCES_KEY_AP_PASSWD, passwd);

    // Save the changes to Preferences
    cleanerData.end();
}

/**
 * @brief This function updates the mDNS (multicast Domain Name System) configuration data in Preferences.
 * 
 * @param mdns ESP32 mDNS
 */
void set_mDNS_WiFi(const char* mdns) {
    cleanerData.begin(CLEANER_PREFERENCES_NAME, false);

    // Write the mDNS string to the appropriate Preferences address
    cleanerData.putString(CLEANER_PREFERENCES_KEY_MDNS, mdns);

    // Save the changes to Preferences
    cleanerData.end();
}

/**
 * @brief  Sets the module configuration parameters in the Preferences.
 * 
 * @param cleaner_conf Pointer to the Cleaner_module_conf structure that contains the module configuration parameters.
 */
void set_module(Cleaner_module_conf *cleaner_conf) {
    cleanerData.begin(CLEANER_PREFERENCES_NAME, false);

    // Write battery configuration parameters to Preferences
    cleanerData.putUInt(CLEANER_PREFERENCES_KEY_BATTERY_PIN, cleaner_conf->battery_conf.pin);
    cleanerData.putUInt(CLEANER_PREFERENCES_KEY_BATTERY_MAX, cleaner_conf->battery_conf.max);
    cleanerData.putUInt(CLEANER_PREFERENCES_KEY_BATTERY_MIN, cleaner_conf->battery_conf.min);

    // Write fan configuration parameter to Preferences
    cleanerData.putUInt(CLEANER_PREFERENCES_KEY_FAN_PIN, cleaner_conf->IRF520_pin);

    // Write MX1584 pinout configuration parameters to Preferences
    cleanerData.putUInt(CLEANER_PREFERENCES_KEY_A01_PIN, cleaner_conf->mx1584_pinout_conf.pin_A01);
    cleanerData.putUInt(CLEANER_PREFERENCES_KEY_A02_PIN, cleaner_conf->mx1584_pinout_conf.pin_A02);
    cleanerData.putUInt(CLEANER_PREFERENCES_KEY_B01_PIN, cleaner_conf->mx1584_pinout_conf.pin_B01);
    cleanerData.putUInt(CLEANER_PREFERENCES_KEY_B02_PIN, cleaner_conf->mx1584_pinout_conf.pin_B02);

    // Write MX1584 PWM configuration parameters to Preferences
    cleanerData.putUInt(CLEANER_PREFERENCES_KEY_A01_PWM, cleaner_conf->mx1584_pwm_conf.channel_A01);
    cleanerData.putUInt(CLEANER_PREFERENCES_KEY_A02_PWM, cleaner_conf->mx1584_pwm_conf.channel_A02);
    cleanerData.putUInt(CLEANER_PREFERENCES_KEY_B01_PWM, cleaner_conf->mx1584_pwm_conf.channel_B01);
    cleanerData.putUInt(CLEANER_PREFERENCES_KEY_B02_PWM, cleaner_conf->mx1584_pwm_conf.channel_B02);

    // Save changes to Preferences
    cleanerData.end();
}