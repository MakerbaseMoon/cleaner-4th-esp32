#include <ESPAsyncWebServer.h>
#include <DNSServer.h>
// #include <SPIFFS.h>
#include <WiFi.h>

#include "components/website.h"
#include "components/setting.h"

IPAddress local_IP(192, 168, 4, 1);

AsyncWebServer server(80);
DNSServer dnsServer;

Cleaner_module_conf *_cleaner_module_conf;
Network_conf *_network_conf;

void setup_server(Cleaner_module_conf *cleaner_module_conf, Network_conf *network_conf) {
    // if(!SPIFFS.begin()) {
    //     while(1);
    // }

    _cleaner_module_conf = cleaner_module_conf;
    _network_conf        = network_conf;

    dnsServer.start(53, "*", local_IP);

    setup_api();
    setup_website();

    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
    server.begin();
}

void loop_server() {
    dnsServer.processNextRequest();
}

void setup_website() {
    // [GET] http://cleaner/ - index
    server.on("/", HTTP_GET, [] (AsyncWebServerRequest *request) {
        AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", index_html, INDEX_HTML_LEN);
        response->addHeader("Content-Encoding", "gzip");
        request->send(response);
    });

    server.on("/static/css/main.c2cab247.css", HTTP_GET, [] (AsyncWebServerRequest *request) {
        AsyncWebServerResponse *response = request->beginResponse_P(200, "text/css", main_c2cab247_css, MAIN_105545EE_JS_LEN);
        response->addHeader("Content-Encoding", "gzip");
        request->send(response);
    });

    server.on("/static/js/main.105545ee.js", HTTP_GET, [] (AsyncWebServerRequest *request) {
        AsyncWebServerResponse *response = request->beginResponse_P(200, "text/javascript", main_105545ee_js, MAIN_105545EE_JS_LEN);
        response->addHeader("Content-Encoding", "gzip");
        request->send(response);
    });

    server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request) {
        AsyncWebServerResponse *response = request->beginResponse_P(200, "image/jpg", favicon, FAVICON_LEN);
        request->send(response);
    });

    server.on("/favicon.jpg", HTTP_GET, [](AsyncWebServerRequest *request) {
        AsyncWebServerResponse *response = request->beginResponse_P(200, "image/jpg", favicon, FAVICON_LEN);
        request->send(response);
    });

    server.on("/maker.jpg", HTTP_GET, [](AsyncWebServerRequest *request) {
        AsyncWebServerResponse *response = request->beginResponse_P(200, "image/jpg", maker, MAKER_LEN);
        request->send(response);
    });

    server.on("/cleaner.png", HTTP_GET, [](AsyncWebServerRequest *request) {
        AsyncWebServerResponse *response = request->beginResponse_P(200, "image/jpg", cleaner, CLEANER_LEN);
        request->send(response);
    });

    server.onNotFound([](AsyncWebServerRequest *request){
        char *redirect_url = (char *)malloc( sizeof(char) * 25 );
        sprintf(redirect_url, "http://%s/", request->client()->localIP().toString().c_str());
        request->redirect(redirect_url);
        free(redirect_url);
    });
}

void setup_api() {
    // [POST] http://cleaner/api/mode - Mode setting
    server.on("/api/mode/", HTTP_POST, [] (AsyncWebServerRequest *request) {
        motor_stop();

        int params = request->params();
        Serial.printf("[POST]/api/mode: \n");
        for (int i = 0; i < params; i++){
            AsyncWebParameter *p = request->getParam(i);
            Serial.printf("name: %s, value %s\n", p->name().c_str(), p->value().c_str());
            if(p->name().indexOf("mode") == 0) {
                int num = atoi(p->value().c_str());
                switch(num) {
                    // OTA Mode
                    case 0:
                        motor_stop();
                        break;

                    // Auto Mode
                    case 1:
                        motor_stop();
                        break;
                    
                    // Control Mode
                    case 2:
                        motor_stop();
                        break;

                    // Other Mode
                    default:
                        motor_stop();
                        break;
                }
            }
        }

        request->send(200, "application/json", "{\"url\":\"/api/mode\",\"status\":\"susses\"}");
    });

    // [POST] http://cleaner/api/motor/stop - Motor stop
    server.on("/api/motor/stop", HTTP_POST, [] (AsyncWebServerRequest *request) {
        motor_stop();

        int params = request->params();
        Serial.printf("[POST]/api/motor/stop: \n");
        for (int i = 0; i < params; i++){
            AsyncWebParameter *p = request->getParam(i);
            Serial.printf("name: %s, value %s\n", p->name().c_str(), p->value().c_str());
        }

        request->send(200, "application/json", "{\"url\":\"/api/motor/stop\",\"status\":\"susses\"}");
    });

    // [POST] http://cleaner/api/motor/run - [0]Motor stop
    server.on("/api/motor/run", HTTP_POST, [] (AsyncWebServerRequest *request) {
        motor_stop();

        int params = request->params();
        Serial.printf("[POST]/api/motor/run: \n");
        for (int i = 0; i < params; i++){
            AsyncWebParameter *p = request->getParam(i);
            Serial.printf("name: %s, value: %s\n", p->name().c_str(), p->value().c_str());
            if(p->name().indexOf("run") == 0) {
                int num = atoi(p->value().c_str());
                switch(num) {
                    case 0:
                        motor_stop();
                        break;

                    case 1:
                        motor_forward();
                        break;

                    case 2:
                        motor_backward();
                        break;

                    case 3:
                        motor_left();
                        break;

                    case 4:
                        motor_right();
                        break;
                    
                    default:
                        motor_stop();
                        break;
                }
            }
        }

        request->send(200, "application/json", "{\"url\":\"/api/motor/run\",\"status\":\"susses\"}");
    });

    // [POST] http://cleaner/api/fan/pwm - [0-255]fan pwm
    server.on("/api/fan/pwm", HTTP_POST, [] (AsyncWebServerRequest *request) {
        int params = request->params();
        Serial.printf("[POST]/fan/pwm/run: \n");
        for (int i = 0; i < params; i++){
            AsyncWebParameter *p = request->getParam(i);
            Serial.printf("name: %s, value: %s\n", p->name().c_str(), p->value().c_str());
            if(p->name().indexOf("pwm") == 0) {
                set_IRF520_PWM(atoi(p->value().c_str()));
            }
        }

        request->send(200, "application/json", "{\"url\":\"/api/motor/run\",\"status\":\"susses\"}");
    });

    // [POST] http://cleaner/api/set/network - Set EEPROM WiFi STA or AP or mDNS
    server.on("/api/set/network", HTTP_POST, [] (AsyncWebServerRequest *request) {
        
        int params = request->params();
        Serial.printf("[POST]/api/set/network: \n");
        for (int i = 0; i < params; i++){
            AsyncWebParameter *p = request->getParam(i);
            Serial.printf("name: %s, value %s\n", p->name().c_str(), p->value().c_str());
        }

        request->send(200, "application/json", "{\"url\":\"/api/set/network\",\"status\":\"susses\"}");
    });

    // [POST] http://cleaner/api/set/module - Set EEPROM module pinout
    server.on("/api/set/module", HTTP_POST, [] (AsyncWebServerRequest *request) {
        
        int params = request->params();
        Serial.printf("[POST]/api/set/module: \n");
        for (int i = 0; i < params; i++){
            AsyncWebParameter *p = request->getParam(i);
            Serial.printf("name: %s, value %s\n", p->name().c_str(), p->value().c_str());
        }

        request->send(200, "application/json", "{\"url\":\"/api/set/module\",\"status\":\"susses\"}");
    });

    // [POST] http://cleaner/api/get/network - Get EEPROM WiFi STA and AP and mDNS
    server.on("/api/get/network", HTTP_GET, [] (AsyncWebServerRequest *request) {
        char *network_data = (char *)malloc( sizeof(char) * 350 ); // Data: 155, mDNS: 25, MAC: 17, AP SSID: 25, AP Password: 25, AP IP: 14 , STA SSID: 25, STA Password: 25, STA IP: 14 -> 325(350)

        if(network_data != NULL) {
            sprintf(network_data, "{\"url\":\"/api/get/network\",\"status\":\"susses\",\"mDNS\":\"%s\",\"MAC\":\"%s\",\"ap\":{\"ssid\":\"%s\",\"passwd\":\"%s\",\"ip\":\"%s\"},\"sta\":{\"ssid\":\"%s\",\"passwd\":\"%s\",\"ip\":\"%s\"}}",
                *(_network_conf->mdns), WiFi.macAddress().c_str(), 
                *(_network_conf->ap_conf. ssid), *(_network_conf->ap_conf. passwd), WiFi.softAPIP().toString().c_str(),
                *(_network_conf->sta_conf.ssid), *(_network_conf->sta_conf.passwd), WiFi. localIP().toString().c_str());
            request->send(200, "application/json", network_data);
        } else {
            request->send(400, "application/json", "{\"url\":\"/api/get/network\",\"status\":\"error\",\"message\":\"The network data was null\"}");
        }
        free(network_data);
    });

    // [POST] http://cleaner/api/get/module - Get EEPROM module pinout
    server.on("/api/get/module", HTTP_POST, [] (AsyncWebServerRequest *request) {
        char *module_data = (char *)malloc( sizeof(char) * 250 ); // Data: 197 + value (1 Byte) * 12 -> 250
        if(module_data != NULL) {
            sprintf(module_data, "{\"url\":\"/api/get/module\",\"status\":\"susses\",\"mx1584\":{\"pinout\":{\"A01\":%u,\"A02\":%u,\"B01\":%u,\"B02\":%u},\"pwm\":{\"A01\":%u,\"A02\":%u,\"B01\":%u,\"B02\":%u}},\"fan\":%u,\"battery\":{\"pinout\":%u,\"min\":%u,\"max\":%u}}",
                _cleaner_module_conf->mx1584_pinout_conf.pin_A01, _cleaner_module_conf->mx1584_pinout_conf.pin_A02, _cleaner_module_conf->mx1584_pinout_conf.pin_B01, _cleaner_module_conf->mx1584_pinout_conf.pin_B02,
                _cleaner_module_conf->mx1584_pwm_conf.channel_A01, _cleaner_module_conf->mx1584_pwm_conf.channel_A02, _cleaner_module_conf->mx1584_pwm_conf.channel_B01, _cleaner_module_conf->mx1584_pwm_conf.channel_B02,
                _cleaner_module_conf->IRF520_pin , 
                _cleaner_module_conf->battery_conf.pin, _cleaner_module_conf->battery_conf.min, _cleaner_module_conf->battery_conf.max
                );
            request->send(200, "application/json", module_data);
        } else {
            request->send(400, "application/json", "{\"url\":\"/api/get/module\",\"status\":\"error\",\"message\":\"The module data was null\"}");
        }
        free(module_data);
    });

    // [POST] http://cleaner/api/esp/restart- Set ESP32 to restart
    server.on("/api/esp/restart", HTTP_POST, [] (AsyncWebServerRequest *request) {
        request->send(200, "application/json", "{\"url\":\"/api/esp/restart\",\"status\":\"susses\"}");
        delay(5000);
        ESP.restart();
    });

    // [POST] http://cleaner/api/esp/sleep- Set ESP32 to sleep
    server.on("/api/esp/sleep", HTTP_POST, [] (AsyncWebServerRequest *request) {
        request->send(200, "application/json", "{\"url\":\"/api/esp/sleep\",\"status\":\"susses\"}");
        ESP.deepSleep(100000);
    });

    // [POST] http://cleaner/api/esp/info- Get ESP32 info
    server.on("/api/esp/info", HTTP_POST, [] (AsyncWebServerRequest *request) {
        char *json_str = (char *)malloc( sizeof(char) * 500 );
        if(json_str != NULL) {
            sprintf(json_str,
            "{\"url\":\"/api/get/module\",\"status\":\"susses\",\"HeapSize\":%u,\"FreeHeap\":%u,\"MinFreeHeap\":%u,\"MaxAllocHeap\":%u,\"SketchSize\":%u,\"FreeSketchSpace\":%u,\"ChipRevision\":%u,\"ChipModel\":\"%s\",\"ChipCores\":%u,\"SdkVersion\":\"%s\",\"FlashChipSize\":%u,\"FlashChipSpeed\":%u}",
                ESP.getHeapSize(),
                ESP.getFreeHeap(),
                ESP.getMinFreeHeap(),
                ESP.getMaxAllocHeap(),
                ESP.getSketchSize(),
                ESP.getFreeSketchSpace(),
                ESP.getChipRevision(),
                ESP.getChipModel(),
                ESP.getChipCores(),
                ESP.getSdkVersion(),
                ESP.getFlashChipSize(),
                ESP.getFlashChipSpeed()
            );
            request->send(200, "application/json", json_str);
        } else {
            request->send(400, "application/json", "{\"url\":\"/api/get/module\",\"status\":\"error\",\"message\":\"The module data was null\"}");
        }
    });
}
