#include "components/module.h"

#include "header.h"

MX1584_pwm_conf *_pwm_conf;

/**
 * @brief Set up the MX1584 motor driver with the given pinout and PWM configurations
 * 
 * @param pinout_conf Pinout configuration for the MX1584 motor driver
 * @param pwm_conf    PWM configuration for the MX1584 motor driver
 */
void setup_MX1584(MX1584_pinout_conf *pinout_conf, MX1584_pwm_conf *pwm_conf) {
    _pwm_conf = pwm_conf;

    // Set up the LEDC timers for the four motor driver channels
    ledcSetup(CLEANER_DEFAULT_MOTOR_A01_CHANNEL, CLEANER_DEFAULT_LEDC_FREQ, CLEANER_DEFAULT_LEDC_RESOLUTION);
    ledcSetup(CLEANER_DEFAULT_MOTOR_A02_CHANNEL, CLEANER_DEFAULT_LEDC_FREQ, CLEANER_DEFAULT_LEDC_RESOLUTION);
    ledcSetup(CLEANER_DEFAULT_MOTOR_B01_CHANNEL, CLEANER_DEFAULT_LEDC_FREQ, CLEANER_DEFAULT_LEDC_RESOLUTION);
    ledcSetup(CLEANER_DEFAULT_MOTOR_B02_CHANNEL, CLEANER_DEFAULT_LEDC_FREQ, CLEANER_DEFAULT_LEDC_RESOLUTION);

    // Attach the LEDC timers to the motor driver pins
    ledcAttachPin(pinout_conf->pin_A01, CLEANER_DEFAULT_MOTOR_A01_CHANNEL);
    ledcAttachPin(pinout_conf->pin_A02, CLEANER_DEFAULT_MOTOR_A02_CHANNEL);
    ledcAttachPin(pinout_conf->pin_B01, CLEANER_DEFAULT_MOTOR_B01_CHANNEL);
    ledcAttachPin(pinout_conf->pin_B02, CLEANER_DEFAULT_MOTOR_B02_CHANNEL);
}

/**
 * @brief Stop all motors
 * 
 */
void motor_stop() {
    ledcWrite(CLEANER_DEFAULT_MOTOR_A01_CHANNEL, 0);
    ledcWrite(CLEANER_DEFAULT_MOTOR_A02_CHANNEL, 0);
    ledcWrite(CLEANER_DEFAULT_MOTOR_B01_CHANNEL, 0);
    ledcWrite(CLEANER_DEFAULT_MOTOR_B02_CHANNEL, 0);
}

/**
 * @brief Move forward
 * 
 */
void motor_forward() {
    set_motor_speed(true, false, true, false);
}

/**
 * @brief Move backward
 * 
 */
void motor_backward() {
    set_motor_speed(false, true, false, true);
}

/**
 * @brief Turn left
 * 
 */
void motor_left() {
    set_motor_speed(true, false, false, true);
}

/**
 * @brief Turn right
 * 
 */
void motor_right() {
    set_motor_speed(false, true, true, false);
}

/**
 * @brief Set the speed of the four motors
 * 
 * @param A01_enable Flag indicating if motor A01 should be enabled
 * @param A02_enable Flag indicating if motor A02 should be enabled
 * @param B01_enable Flag indicating if motor B01 should be enabled
 * @param B02_enable Flag indicating if motor B02 should be enabled
 */
void set_motor_speed(boolean A01_enable, boolean A02_enable, boolean B01_enable, boolean B02_enable) {
    ledcWrite(CLEANER_DEFAULT_MOTOR_A01_CHANNEL, A01_enable? 0 : _pwm_conf->channel_A01);
    ledcWrite(CLEANER_DEFAULT_MOTOR_A02_CHANNEL, A02_enable? 0 : _pwm_conf->channel_A02);
    ledcWrite(CLEANER_DEFAULT_MOTOR_B01_CHANNEL, B01_enable? 0 : _pwm_conf->channel_B01);
    ledcWrite(CLEANER_DEFAULT_MOTOR_B02_CHANNEL, B02_enable? 0 : _pwm_conf->channel_B02);
}