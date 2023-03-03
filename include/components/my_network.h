#ifndef __CLEANER_MY_NETWORK_H__
#define __CLEANER_MY_NETWORK_H__

#include <Arduino.h>

#include "module.h"

struct Network_STA_conf {
    char **ssid;
    char **passwd;
};

struct Network_AP_conf {
    char **ssid;
    char **passwd;
};


struct Network_conf {
    Network_STA_conf sta_conf;
    Network_AP_conf  ap_conf;
    char **mdns;
};

void setup_server(Cleaner_module_conf *cleaner_module_conf, Network_conf *network_conf);
void loop_server();

void setup_website();
void setup_api();

void setup_wifi(Network_conf *network_conf);

#endif