#ifndef __CLEANER_MODULE_H__
#define __CLEANER_MODULE_H__

#include <Arduino.h>

// Battery.cpp
struct Battery_conf {
    uint8_t  pin;  // The analog input pin for the battery sensor
    uint16_t max;  // The maximum analog input value for a fully charged battery
    uint16_t min;  // The minimum analog input value for an empty battery
};

void setup_battery(Battery_conf *conf);
uint8_t get_electricity();

// MX1584.cpp

// Define the pinout configuration for the MX1584 motor driver
struct MX1584_pinout_conf {
    uint8_t pin_A01;
    uint8_t pin_A02;
    uint8_t pin_B01;
    uint8_t pin_B02;
};

// Define the PWM configuration for the MX1584 motor driver
struct MX1584_pwm_conf {
    uint8_t channel_A01;
    uint8_t channel_A02;
    uint8_t channel_B01;
    uint8_t channel_B02;
};

void setup_MX1584(MX1584_pinout_conf *pinout_conf, MX1584_pwm_conf *pwm_conf);

void motor_stop();
void motor_forward();
void motor_backward();
void motor_left();
void motor_right();

void set_motor_speed(boolean A01_enable, boolean A02_enable, boolean B01_enable, boolean B02_enable);

// IRF520.cpp
void setup_IRF520(uint8_t pin);
void set_IRF520_PWM(uint32_t duty);

// SSD1306.cpp
void setup_SSD1306();
void show_logo();
void show_dashboard(uint8_t mode);
void show_dashboard_battery_20();
void show_dashboard_wifi_20();
void show_dashboard_body(uint8_t mode);
void show_dashboard_battery();

// VL53L0X.cpp
struct VL53L0X_value{
    int32_t left;
    int32_t right;
};

void setup_VL53L0X();
VL53L0X_value loop_VL53L0X();

// module.cpp
struct Cleaner_module_conf {
    uint8_t             IRF520_pin;
    Battery_conf        battery_conf;
    MX1584_pwm_conf     mx1584_pwm_conf;
    MX1584_pinout_conf  mx1584_pinout_conf;
};

void setup_module(Cleaner_module_conf *cleaner_module_conf);

// OLED SSD1306.cpp
#define SCREEN_WIDTH   128
#define SCREEN_HEIGHT   64
#define OLED_ADDRESS  0x3C

#define IMAGE_WIDTH    128
#define IMAGE_HEIGHT    64


#endif