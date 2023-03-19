#include <Arduino.h>

#include "components/ota.h"
#include "components/module.h"
#include "components/setting.h"
#include "components/my_network.h"

TaskHandle_t Task1;

void Task1code(void* parameter);

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
    Serial.begin(115200);
    while(!Serial);

    setup_data(&my_cleaner_conf, &network_conf);
    setup_module(&my_cleaner_conf);
    
    setup_wifi(&network_conf);
    setup_server(&my_cleaner_conf, &network_conf, &cleaner_mode, &url);

    xTaskCreatePinnedToCore(Task1code, "Task1", 10240, NULL, 1, &Task1, 1);
    delay(500);
}

void loop() {
    loop_server();
    if(cleaner_mode == 0) { // OTA mode.
        if(!update_loop(url)) {
            cleaner_mode = 2;
            ESP.restart();
        } else {
            cleaner_mode = 2;
        }
    } else if(cleaner_mode == 1) { // Game mode.

    } else if(cleaner_mode == 2) { // Auto mode.

    }
}

void Task1code(void* parameter) {
    uint16_t k = 0;

    for(;;) {
        VL53L0X_value value = loop_VL53L0X();
        Serial.printf("%d\t%d\n", value.left, value.right);

        if( k >= 29 ) {
            show_dashboard(cleaner_mode);
            k = 0;
        }

        k++;
        vTaskDelay(30 / portTICK_PERIOD_MS);
    }
}
