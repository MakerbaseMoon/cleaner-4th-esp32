# Setting

## my_eeprom.cpp
- `void set_STA_WiFi(const char* ssid, const char* passwd)`: This function updates the STA (station) mode WiFi network configuration data in EEPROM.
- `void get_network_conf(Network_conf *network_conf)`: This function reads the network configuration data from EEPROM and updates the provided Network_conf struct.
- `void get_module_conf(Cleaner_module_conf *cleaner_conf)`: This function reads the module configuration data from EEPROM and updates the provided Cleaner_module_conf struct.