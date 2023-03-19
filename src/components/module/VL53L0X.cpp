#include <Adafruit_VL53L0X.h>
#include <Wire.h>

#include "components/module.h"

Adafruit_VL53L0X sensor_left  = Adafruit_VL53L0X();
Adafruit_VL53L0X sensor_right = Adafruit_VL53L0X();

void setup_VL53L0X() {
    sensor_left. begin(VL53L0X_I2C_ADDR, false, &Wire1);
    sensor_right.begin(VL53L0X_I2C_ADDR, false, &Wire); 
}

VL53L0X_value loop_VL53L0X() {
    VL53L0X_value value;

    VL53L0X_RangingMeasurementData_t measure_left;
    VL53L0X_RangingMeasurementData_t measure_right;

    sensor_left. rangingTest(&measure_left, false);
    sensor_right.rangingTest(&measure_right, false);

    if(measure_left.RangeStatus != 4) {
        value.left = measure_left.RangeMilliMeter;
    } else {
        value.left = -1;
    }

    if(measure_right.RangeStatus != 4) {
        value.right = measure_right.RangeMilliMeter;
    } else {
        value.right = -1;
    }

    return value;
}