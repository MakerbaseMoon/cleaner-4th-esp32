#include <Arduino.h>

#include "components/module.h"
#include "components/setting.h"
#include "components/my_network.h"

// TaskHandle_t Task1;
// TaskHandle_t Task2;

// void Task1code(void* parameter);
// void Task2code(void* parameter);

char *sta_ssid   = NULL;
char *sta_passwd = NULL;
char *ap_ssid    = NULL;
char *ap_passwd  = NULL;
char *mdns       = NULL;

Cleaner_module_conf my_cleaner_conf;

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
    setup_server(&my_cleaner_conf, &network_conf);

    show_dashboard(2, 0);
    
    // delay(1000);
    // xTaskCreatePinnedToCore(Task1code, "Task1", 1024, NULL, 1, &Task1, 1);                         
    // delay(500); 

    // xTaskCreatePinnedToCore(Task2code, "Task2", 10000, NULL, 1, &Task2, 1);          
    // delay(500);  
}

void loop() {
    loop_server();

    // show_dashboard(2, 0);
    // delay(1000);
    // show_dashboard(2, 0);
    // delay(1000);
    
    // show_dashboard(1, 50);
    // delay(1000);
    // show_dashboard(1, 50);
    // delay(1000);

    // show_dashboard(0, 100);
    // delay(1000);
    // show_dashboard(0, 100);
    // delay(1000);

}

// void Task1code(void* parameter) {
//     for(;;) {
//         Serial.printf("Hello World!\n");
//         vTaskDelay(1000 / portTICK_PERIOD_MS);
//     }
// }

// void Task2code(void* parameter) {
//     for(;;) {
//         delay(1000);
//     }
// }
