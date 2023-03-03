#include "components/module.h"

Battery_conf *_battery_conf;

/**
 * @brief Set up the battery sensor by setting the pinMode for the specified pin to INPUT.
 * 
 * @param conf A pointer to a Battery_conf struct that contains the configuration for the battery sensor
 */
void setup_battery(Battery_conf *conf) {
    _battery_conf = conf;
    pinMode(_battery_conf->pin, INPUT);
}

/**
 * @brief Get the current battery level as a percentage.
 * 
 * @param conf A pointer to a Battery_conf struct that contains the configuration for the battery sensor
 * @return The current battery level as a percentage, or 0 if an error occurs
 */
uint8_t get_electricity() {
    uint16_t electricity = analogRead(_battery_conf->pin);

    if(electricity < _battery_conf->min) {
        return 0;
    }

    if(electricity > _battery_conf->max) {
        return 100;
    }

    // Scale the analog input value to a percentage between 0 and 100
    return (uint8_t)((float)(electricity - _battery_conf->min) / (_battery_conf->max - _battery_conf->min) * 100);
}
