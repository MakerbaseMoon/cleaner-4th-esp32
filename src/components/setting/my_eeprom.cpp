#include <EEPROM.h>

#include "components/setting.h"

/**
 * @brief Initialize the EEPROM memory and load the stored configuration settings.
 * 
 * @param cleaner_conf Cleaner module conf
 * @param network_conf Network conf
 */
void setup_eeprom(Cleaner_module_conf *cleaner_conf, Network_conf *network_conf) {
    if(!EEPROM.begin(255)) {
        while(1);
    }

    // Verify the integrity of the stored configuration data.
    // If the data is corrupted, erase the memory and load the default configuration.
    for(int i = EEPROM_CHECK_START; i <= EEPROM_CHECK_END; i++) {
        if(EEPROM.read(i) != EEPROM_CHECK_NUM) {
            clean_all_eeprom();
            set_default_eeprom();
            break;
        }
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

    // Load the network and module configuration data from EEPROM.
    get_network_conf(network_conf);
    get_module_conf (cleaner_conf);
}

/**
 * @brief Read the network configuration data from EEPROM and update the provided Network_conf struct.
 * 
 * @param network_conf Network conf
 */
void get_network_conf(Network_conf *network_conf) {
    EEPROM.readBytes(EEPROM_SSID_ADDRESS,   (void *)(*(network_conf->sta_conf.ssid)),   EEPROM_MAX_LEN);
    EEPROM.readBytes(EEPROM_PASSWD_ADDRESS, (void *)(*(network_conf->sta_conf.passwd)), EEPROM_MAX_LEN);

    EEPROM.readBytes(EEPROM_AP_SSID_ADDRESS,   (void *)(*(network_conf->ap_conf.ssid)),   EEPROM_MAX_LEN);
    EEPROM.readBytes(EEPROM_AP_PASSWD_ADDRESS, (void *)(*(network_conf->ap_conf.passwd)), EEPROM_MAX_LEN);

    EEPROM.readBytes(EEPROM_MDNS_ADDRESS, (void *)(*(network_conf->mdns)), EEPROM_MAX_LEN);
}

/**
 * @brief Read the module configuration data from EEPROM and update the provided Cleaner_module_conf struct.
 * 
 * @param cleaner_conf Cleaner module conf
 */
void get_module_conf(Cleaner_module_conf *cleaner_conf) {
    // Read the battery pin number from EEPROM
    cleaner_conf->battery_conf.pin = EEPROM.read(EEPROM_BATTERY_PIN);

    // Read the battery maximum and minimum voltage levels from EEPROM
    EEPROM.readBytes(EEPROM_BATTERY_MAX, (void *)(&(cleaner_conf->battery_conf.max)), 2);
    EEPROM.readBytes(EEPROM_BATTERY_MIN, (void *)(&(cleaner_conf->battery_conf.min)), 2);

    // Read the fan pin number from EEPROM
    cleaner_conf->IRF520_pin = EEPROM.read(EEPROM_FAN_PIN);

    // Read the MX1584 module pinout configuration from EEPROM
    cleaner_conf->mx1584_pinout_conf.pin_A01 = EEPROM.read(EEPROM_MX1584_A01_PIN);
    cleaner_conf->mx1584_pinout_conf.pin_A02 = EEPROM.read(EEPROM_MX1584_A02_PIN);
    cleaner_conf->mx1584_pinout_conf.pin_B01 = EEPROM.read(EEPROM_MX1584_B01_PIN);
    cleaner_conf->mx1584_pinout_conf.pin_B02 = EEPROM.read(EEPROM_MX1584_B02_PIN);

    // Read the MX1584 module PWM channel configuration from EEPROM
    cleaner_conf->mx1584_pwm_conf.channel_A01 = EEPROM.read(EEPROM_MX1584_A01_PWM);
    cleaner_conf->mx1584_pwm_conf.channel_A02 = EEPROM.read(EEPROM_MX1584_A02_PWM);
    cleaner_conf->mx1584_pwm_conf.channel_B01 = EEPROM.read(EEPROM_MX1584_B01_PWM);
    cleaner_conf->mx1584_pwm_conf.channel_B02 = EEPROM.read(EEPROM_MX1584_B02_PWM);
}

/**
 * @brief This function updates the STA (station) mode WiFi network configuration data in EEPROM.
 * 
 * @param ssid STA SSID
 * @param passwd STA Password
 */
void set_STA_WiFi(const char* ssid, const char* passwd) {
    // Write the SSID and password strings to the appropriate EEPROM addresses
    EEPROM.writeBytes(EEPROM_SSID_ADDRESS,   (void *)ssid,   strlen(ssid));
    EEPROM.write(EEPROM_SSID_ADDRESS   + strlen(ssid),   0);

    EEPROM.writeBytes(EEPROM_PASSWD_ADDRESS, (void *)passwd, strlen(passwd));
    EEPROM.write(EEPROM_PASSWD_ADDRESS + strlen(passwd), 0);

    // Save the changes to EEPROM
    EEPROM.commit();
}

/**
 * @brief This function updates the AP (access point) mode WiFi network configuration data in EEPROM.
 * 
 * @param ssid AP mode SSID
 * @param passwd AP mode Password
 */
void set_AP_WiFi(const char* ssid, const char* passwd) {
    // Write the SSID and password strings to the appropriate EEPROM addresses
    EEPROM.writeBytes(EEPROM_AP_SSID_ADDRESS,   (void *)ssid,   strlen(ssid));
    EEPROM.write(EEPROM_AP_SSID_ADDRESS   + strlen(ssid),   0);

    EEPROM.writeBytes(EEPROM_AP_PASSWD_ADDRESS, (void *)passwd, strlen(passwd));
    EEPROM.write(EEPROM_AP_PASSWD_ADDRESS + strlen(passwd), 0);

    // Save the changes to EEPROM
    EEPROM.commit();
}

/**
 * @brief This function updates the mDNS (multicast Domain Name System) configuration data in EEPROM.
 * 
 * @param mdns ESP32 mDNS
 */
void set_mDNS_WiFi(const char* mdns) {
    // Write the mDNS string to the appropriate EEPROM address
    EEPROM.writeBytes(EEPROM_MDNS_ADDRESS, (void *)mdns, strlen(mdns));
    EEPROM.write(EEPROM_MDNS_ADDRESS + strlen(mdns), 0);

    // Save the changes to EEPROM
    EEPROM.commit();
}

/**
 * @brief  Sets the module configuration parameters in the EEPROM.
 * 
 * @param cleaner_conf Pointer to the Cleaner_module_conf structure that contains the module configuration parameters.
 */
void set_module(Cleaner_module_conf *cleaner_conf) {
    // Write battery configuration parameters to EEPROM
    EEPROM.write(EEPROM_BATTERY_PIN, cleaner_conf->battery_conf.pin);

    EEPROM.writeBytes(EEPROM_BATTERY_MAX, (void *)(&cleaner_conf->battery_conf.max), 2);
    EEPROM.writeBytes(EEPROM_BATTERY_MIN, (void *)(&cleaner_conf->battery_conf.min), 2);

    // Write fan configuration parameter to EEPROM
    EEPROM.write(EEPROM_FAN_PIN, cleaner_conf->IRF520_pin);

    // Write MX1584 pinout configuration parameters to EEPROM
    EEPROM.write(EEPROM_MX1584_A01_PIN, cleaner_conf->mx1584_pinout_conf.pin_A01);
    EEPROM.write(EEPROM_MX1584_A02_PIN, cleaner_conf->mx1584_pinout_conf.pin_A02);
    EEPROM.write(EEPROM_MX1584_B01_PIN, cleaner_conf->mx1584_pinout_conf.pin_B01);
    EEPROM.write(EEPROM_MX1584_B02_PIN, cleaner_conf->mx1584_pinout_conf.pin_B02);

    // Write MX1584 PWM configuration parameters to EEPROM
    EEPROM.write(EEPROM_MX1584_A01_PWM, cleaner_conf->mx1584_pwm_conf.channel_A01);
    EEPROM.write(EEPROM_MX1584_A02_PWM, cleaner_conf->mx1584_pwm_conf.channel_A02);
    EEPROM.write(EEPROM_MX1584_B01_PWM, cleaner_conf->mx1584_pwm_conf.channel_B01);
    EEPROM.write(EEPROM_MX1584_B02_PWM, cleaner_conf->mx1584_pwm_conf.channel_B02);

    // Save changes to EEPROM
    EEPROM.commit();
}

/**
 * @brief Sets the default EEPROM values for the cleaner module.
 * 
 */
void set_default_eeprom() {
    // EEPROM by Network
    set_STA_WiFi (CLEANER_DEFAULT_STA_SSID, CLEANER_DEFAULT_STA_PASSWD);
    set_AP_WiFi  (CLEANER_DEFAULT_AP_SSID, CLEANER_DEFAULT_AP_PASSWD);
    set_mDNS_WiFi(CLEANER_DEFAULT_MDNS);

    // EEPROM by Battery
    Battery_conf default_battery_conf = {
        .pin = CLEANER_DEFAULT_BATTERY,
        .max = CLEANER_DEFAULT_BATTERY_MAX_VALUE,
        .min = CLEANER_DEFAULT_BATTERY_MIN_VALUE,
    };

    // EEPROM by MX1584 pinout
    MX1584_pinout_conf default_mx1584_pinout_conf = {
        .pin_A01 = CLEANER_DEFAULT_MOTOR_A01,
        .pin_A02 = CLEANER_DEFAULT_MOTOR_A02,
        .pin_B01 = CLEANER_DEFAULT_MOTOR_B01,
        .pin_B02 = CLEANER_DEFAULT_MOTOR_B02,
    };

    // EEPROM by MX1584 pwm
    MX1584_pwm_conf default_mx1584_pwm_conf = {
        .channel_A01 = CLEANER_DEFAULT_MOTOR_PWM,
        .channel_A02 = CLEANER_DEFAULT_MOTOR_PWM,
        .channel_B01 = CLEANER_DEFAULT_MOTOR_PWM,
        .channel_B02 = CLEANER_DEFAULT_MOTOR_PWM,
    };

    
    Cleaner_module_conf default_cleaner_conf = {
        .IRF520_pin         = CLEANER_DEFAULT_FAN, // EEPROM by Fan
        .battery_conf       = default_battery_conf,
        .mx1584_pwm_conf    = default_mx1584_pwm_conf,
        .mx1584_pinout_conf = default_mx1584_pinout_conf,
    };

    set_module(&default_cleaner_conf);

    // EEPROM by check
    for(int i = EEPROM_CHECK_START; i <= EEPROM_CHECK_END; i++) {
        EEPROM.write(i, EEPROM_CHECK_NUM);
    }

    EEPROM.commit();
}

/**
 * @brief Clean all eeprom data to 255
 * 
 */
void clean_all_eeprom() {
    for(int k = 0; k < 255; k++) {
        EEPROM.write(k, 255);
    }
}