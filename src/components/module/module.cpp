#include <Wire.h>

#include "header.h"
#include "components/module.h"

void setup_module(Cleaner_module_conf *cleaner_module_conf) {
    Wire. begin(CLEANER_DEFAULT_I2C_SDA,  CLEANER_DEFAULT_I2C_SCL);
    Wire1.begin(CLEANER_DEFAULT_I2C2_SDA, CLEANER_DEFAULT_I2C2_SCL);

    setup_MX1584(&(cleaner_module_conf->mx1584_pinout_conf), &(cleaner_module_conf->mx1584_pwm_conf));
    setup_IRF520(cleaner_module_conf->IRF520_pin);
    setup_battery(&(cleaner_module_conf->battery_conf));
    setup_SSD1306();
    setup_VL53L0X();
}
