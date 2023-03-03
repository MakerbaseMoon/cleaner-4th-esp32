#include "components/module.h"

#include "header.h"

/**
 * @brief Sets up the IRF520 object for controlling a fan with PWM
 * 
 * @param pin The pin used to control the fan
 */
void setup_IRF520(uint8_t pin) {
    ledcSetup(CLEANER_DEFAULT_FAN_CHANNEL, CLEANER_DEFAULT_LEDC_FREQ, CLEANER_DEFAULT_LEDC_RESOLUTION);
    ledcAttachPin(pin, CLEANER_DEFAULT_FAN_CHANNEL);
}

/**
 * @brief Set the PWM duty cycle for the IRF520 object controlling the fan
 * 
 * @param duty The duty cycle value to set (0-255)
 */
void set_IRF520_PWM(uint32_t duty) {
    ledcWrite(CLEANER_DEFAULT_FAN_CHANNEL, duty);
}