#include "components/module.h"
#include "components/image.h"

#include <Adafruit_SSD1306.h>
#include <WiFi.h>

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

void setup_SSD1306() {
    if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
        ESP_LOGE("SSD1306", "OLED SSD1306 Begin Failed.");
    }
    display.clearDisplay();
    
    show_logo();
}

void show_logo() {
    display.clearDisplay();
    display.drawBitmap  (32, 0, image_logo_64, 64, 64, WHITE);
    display.display();
}

void show_dashboard(uint8_t mode) {
    display.clearDisplay();

    show_dashboard_battery_20();
    display.drawBitmap(6, 22, image_ap_20, 20, 20, WHITE);
    show_dashboard_wifi_20();
    show_dashboard_body(mode);

    display.display();
}

void show_dashboard_battery_20() {
    uint8_t battery_value = get_electricity();

    if(battery_value > 60) {
        display.drawBitmap(6, 1, image_batter_full_20, 20, 20, WHITE);

    } else if(battery_value > 30) {
        display.drawBitmap(6, 1, image_batter_half_20, 20, 20, WHITE);

    } else {
        display.drawBitmap(6, 1, image_batter_20, 20, 20, WHITE);
    }
}

void show_dashboard_wifi_20() {
    if(WiFi.status() == WL_CONNECTED) {
        display.drawBitmap(6, 43, image_wifi_20, 20, 20, WHITE);
    } else {
        display.drawBitmap(6, 43, image_wifi_off_20, 20, 20, WHITE);
    }
}

void show_dashboard_body(uint8_t mode) {
    static int body = 0;
    if(body == 0) {
        body = 1;
        switch (mode) {
            case 0:
                display.drawBitmap(55, 7, image_ota_50, 50, 50, WHITE);
                break;
            case 1:
                display.drawBitmap(55, 7, image_dpad_50, 50, 50, WHITE);
                break;
            case 2:
                display.drawBitmap(55, 7, image_robot_50, 50, 50, WHITE);
                break;
            default:
                break;
        }
    } else if(body == 1)  {
        body = 0;
        show_dashboard_battery();
    }
}

void show_dashboard_battery() {
    uint8_t battery_value = get_electricity();

    display.drawBitmap(55, 7, image_battery_50, 50, 50, WHITE);
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    if(battery_value == 100) {
        display.setCursor(59,26);
    } else if(battery_value == 0){
        display.setCursor(72,26);
    } else {
        display.setCursor(66,26);
    } 
    display.printf("%u", battery_value);
}