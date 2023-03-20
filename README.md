# :robot: ESP32 Robot Vacuum Cleaner 4th

![platform](https://img.shields.io/badge/platform-espressif32%406.0.1-green)
![board](https://img.shields.io/badge/board-esp32doit--devkit--v1-lightgrey)
![framework](https://img.shields.io/badge/framework-arduino-blue)

Welcome to the ESP32 Robot Vacuum Cleaner project! This project uses an ESP32 micro controller and several components to create a smart robot vacuum cleaner that can clean floors autonomously, be controlled through a website, and receive updates through GitHub releases.

## Robot Vacuum Cleaner Project

:globe_with_meridians: [Website For Robot Vacuum Cleaner 4th](https://github.com/MakerbaseMoon/cleaner-4th-website)

## framework

- ESP32 microcontroller
- MX1508 motor driver
- MP1584EN voltage regulator
- 12V battery
- 12V fan
- IRF520 MOSFET
- Two VL53L0X distance sensors
- SSD1306 OLED display

## Installation

To install the project, follow these steps:

1. Clone the repository to your local machine.
2. Open the project in PlatformIO IDE.
3. Upload the code to your ESP32 board.
4. Connect the components according to the schematic.
5. Power on the vacuum cleaner.

## Usage

To use the robot vacuum cleaner, follow these steps:

1. Power on the vacuum cleaner.
2. Connect to the ESP32's Wi-Fi network.
3. Open a web browser and go to the vacuum cleaner's IP address.
4. Use the web interface to control the vacuum cleaner, start or stop cleaning, and view sensor data.
5. The OLED display will show information such as battery level and sensor readings.
6. The robot vacuum cleaner will clean autonomously.

## Updating (OTA)

To update the robot vacuum cleaner's firmware, follow these steps:

1. Create a new release on GitHub.
2. Upload the new firmware file to the release.
3. On the web interface, navigate to the "Update" page.
4. Enter the URL of the new firmware file in the "Update URL" field.
5. Click "Update" to start the firmware update process.

or:

1. Make a new tag in local git.
2. pull tag and the Github action will build firmware.

## Contributing

If you want to contribute to the project, please follow these guidelines:

1. Fork the repository.
2. Create a new branch.
3. Make your changes.
4. Create a pull request.
