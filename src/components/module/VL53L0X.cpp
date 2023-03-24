#include <Adafruit_VL53L0X.h>
#include <Wire.h>

#include "components/module.h"

VL53L0X_value _value = {
    .left = -1,
    .right = -1,
    .left_error = true,
    .right_error = true,
};

Adafruit_VL53L0X sensor_left  = Adafruit_VL53L0X();
Adafruit_VL53L0X sensor_right = Adafruit_VL53L0X();

uint8_t setup_VL53L0X() {
    uint8_t isError = 0;
    
    if(sensor_left.begin(VL53L0X_I2C_ADDR, false, &Wire1)) {
        ESP_LOGE("VL53L0X Left", "Begin error.");
        _value.left_error = true;
        uint8_t isError = 1;
    }
    
    if(sensor_right.begin(VL53L0X_I2C_ADDR, false, &Wire)) {
        ESP_LOGE("VL53L0X Right", "Begin error.");
        _value.right_error = true;
        uint8_t isError = 1;
    }

    return isError;
}

VL53L0X_value loop_VL53L0X() {
    VL53L0X_RangingMeasurementData_t measure_left;
    VL53L0X_RangingMeasurementData_t measure_right;

    if(!_value.left_error) {
        sensor_left. rangingTest(&measure_left, false);
    }

    if(!_value.right_error) {
        sensor_right.rangingTest(&measure_right, false);
    }

    if(!_value.left_error) {
        if(measure_left.RangeStatus != 4) {
            _value.left = measure_left.RangeMilliMeter;
        } else {
            _value.left = -1;
        }
    }

    if(!_value.right_error) {
        if(measure_right.RangeStatus != 4) {
            _value.right = measure_right.RangeMilliMeter;
        } else {
            _value.right = -1;
        }
    }

    return _value;
}