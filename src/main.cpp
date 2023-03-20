#include <Arduino.h>

#include "components/ota.h"
#include "components/module.h"
#include "components/setting.h"
#include "components/my_network.h"

TaskHandle_t Task1;
VL53L0X_value value;

void Task1code(void* parameter);

void autoTask();
uint8_t autoModeNum = 0;

char *sta_ssid   = NULL;
char *sta_passwd = NULL;
char *ap_ssid    = NULL;
char *ap_passwd  = NULL;
char *mdns       = NULL;

Cleaner_module_conf my_cleaner_conf;
String url;

uint8_t cleaner_mode = 2;

Network_STA_conf my_sta_conf = {
    .ssid   = &sta_ssid,
    .passwd = &sta_passwd,
};

Network_AP_conf  my_ap_conf = {
    .ssid   = &ap_ssid,
    .passwd = &ap_passwd,
};

Network_conf network_conf = {
    .sta_conf = my_sta_conf,
    .ap_conf  = my_ap_conf,
    .mdns     = &mdns,
};

void setup() {
    setup_data(&my_cleaner_conf, &network_conf);
    setup_module(&my_cleaner_conf);
    
    setup_wifi(&network_conf);
    setup_server(&my_cleaner_conf, &network_conf, &cleaner_mode, &url);

    xTaskCreatePinnedToCore(Task1code, "Task1", 10240, NULL, 1, &Task1, 1);

    if(get_electricity_value() <= 1500) {
        ESP_LOGW("USB Plugin", "Can not get Battery value, enter USB mode");
        set_IRF520_PWM(0);
        motor_stop();
        cleaner_mode = 1;
    } else {
        set_IRF520_PWM(255);
    }

    delay(500);
}

void loop() {
    loop_server();
    if(cleaner_mode == 0) { // OTA mode.
        motor_stop();
        autoModeNum = 0;
        if(!update_loop(url)) {
            cleaner_mode = 2;
            ESP.restart();
        } else {
            cleaner_mode = 2;
        }
    } else if(cleaner_mode == 1) { // Game mode.
        autoModeNum = 0;
    } else if(cleaner_mode == 2) { // Auto mode.
        autoTask();
    }
}

void Task1code(void* parameter) {
    ESP_LOGI("Task1", "Task1 Start.");
    uint16_t k = 0;

    for(;;) {
        value = loop_VL53L0X();

        if( k >= 29 ) {
            ESP_LOGV("VL53L0X", "%d\t%d", value.left, value.right);
            show_dashboard(cleaner_mode);
            k = 0;
        }

        k++;
        vTaskDelay(30 / portTICK_PERIOD_MS);
    }
}
unsigned long autoModeTurnTime = 0;
void autoTask() {
    if(cleaner_mode != 2) {
        motor_stop();
        return;
    }

    if(autoModeNum == 0) {
        if(( value.left != -1 && value.left <= 50) || (value.right != -1 && value.right <= 50) ) {
            ESP_LOGW("Auto mode", "value < 50, Motor Stop");
            motor_stop();
            autoModeNum = 1;
        } else {
            motor_forward();
        }
    } else if(autoModeNum == 1) {
        if(value.left >= 70 || value.right >= 70) {
            autoModeNum = 2;
        } else {
            motor_backward();
        }
    } else if(autoModeNum == 2) {
        if(value.left > value.right) {
            motor_left();
        } else {
            motor_right();
        }
        autoModeNum = 3;
        autoModeTurnTime = millis();

    } else if(autoModeNum == 3) {
        if(value.left >= 80 && value.right >= 80) {
            motor_stop();
            autoModeNum = 0;
        } 
    }
}
