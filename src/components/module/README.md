# Module
ESP32 Robot Vacuum Cleaner 4th module.
- [Motor (MX1584)](#Motor-MX1584)
- [Battery](#Battery)
- [Fan (IRF520)](#Fan-IRF520)
- [OLED (SSD1306)](#OLED-SSD1306)

## Motor MX1584

This library provides functions to control the MX1584 motor driver using PWM signals. The library allows users to set up the driver with pinout and PWM configurations and control the speed and direction of four motors.

### Set up the motor driver

To set up the MX1584 motor driver, call the `setup_MX1584()` function with the pinout and PWM configurations for the driver. The `MX1584_pinout_conf` and `MX1584_pwm_conf` structures define the pinout and PWM configurations, respectively.

```c
MX1584_pinout_conf pinout_conf = {
    .pin_A01 = 12,
    .pin_A02 = 14,
    .pin_B01 = 17,
    .pin_B02 = 15
};

MX1584_pwm_conf pwm_conf = {
    .channel_A01 = 100,
    .channel_A02 = 100,
    .channel_B01 = 100,
    .channel_B02 = 100
};

setup_MX1584(&pinout_conf, &pwm_conf);
```

### Control the motors

Once the motor driver is set up, you can control the speed and direction of the motors using the following functions:

- `motor_stop()`: Stop all motors.
- `motor_forward()`: Move all motors forward.
- `motor_backward()`: Move all motors backward.
- `motor_left()`: Turn left.
- `motor_right()`: Turn right.

These functions call the `set_motor_speed()` function, which sets the PWM signals to control the speed and direction of the motors. The `set_motor_speed()` function takes four boolean parameters to indicate which motors should be enabled.

```c
void set_motor_speed(boolean A01_enable, boolean A02_enable, boolean B01_enable, boolean B02_enable);
```
