# Temperature sensor sender with ESP8266 and BMP180 battery-powered

This project is designed to run on an ESP8266 board (such as NodeMCU or a similar variant) to read temperature and pressure data from a BMP180 sensor. It sends these values to a remote server at regular intervals (defaulting to 30 seconds).

To interface the BMP180 sensor with the ESP8266, we will connect four pins: VCC, GND, SCL, and SDA. The VCC pin will be linked to the 3.3V pin on the ESP8266 board, while both devices will share a common GND connection. To establish the connection with the I2C terminals on the BMP180 module, we will use the default SPI GPIO pins of the ESP8266.

The default I2C pins for the ESP8266 are as follows:
* GPIO4 (D2) for SDA (Serial Data).
* GPIO5 (D1) for SCL (Serial Clock).

After uploading the firmware, you can easily configure the device by connecting to a captive Wi-Fi portal. This portal allows you to set up your Wi-Fi network, define the remote server URL, and specify the interval in seconds for data transmission. The device will store these settings in flash memory, enabling it to retain the configuration when powered off and on again.

**Disclaimer:**

This is a personal project developed for learning and experimentation purposes. It is not intended for commercial or production use. The code and implementation provided here are not rigorously tested or optimized for robustness and reliability. While efforts have been made to ensure the project's functionality and correctness, there may be limitations, bugs, or security vulnerabilities.

Users are encouraged to use this project responsibly and understand that any use of this code is at their own risk. The author(s) of this project shall not be liable for any damages or losses arising from the use or misuse of the code, including but not limited to data loss, system malfunctions, or any other issues that may arise.

Please exercise caution when applying this project to real-world applications and consider seeking professional advice or further testing for critical or production environments.

## Required hardware
Personally, I use the following board and sensor combination:
* [D1 Mini Nodemcu](https://www.az-delivery.de/en/products/d1-mini) ESP8266 or any other similar variant.
* [BMP180](https://www.az-delivery.de/en/products/azdelivery-gy-68-bmp180-barometrischer-sensor-luftdruck-modul-fur-arduino-und-raspberry-pi) barometric air pressure and temperature sensor.
* (Optional) A power bank.

## How to build and upload with VS Code

Prerequesites:
1. Install the PlatformIO IDE extension in VS Code: Open VS Code, go to the Extensions view by clicking on the Extensions icon in the Activity Bar on the side of the window, search for "PlatformIO IDE," and click "Install."
2. Hardware Drivers: For some boards, you may need to install drivers on your computer to enable communication with the development board.

Once you have these prerequisites in place, you can proceed with the following steps:

1. Clone repository.

```shell
$ git clone https://github.com/jose1984/tempsense
```

2. Open Visual Studio Code and navigate to the folder containing your PlatformIO project (the folder containing `platformio.ini`).

3. VS Code will automatically recognize the presence of the `platformio.ini` file as a PlatformIO project.

4. Use the PlatformIO Toolbar in VS Code to build, upload, and monitor your project on the target hardware. The toolbar provides buttons for common tasks such as `Build`, `Upload`, and `Serial Monitor`.

## Deep sleep mode

The ESP8266 deep sleep mode offers significant power consumption reduction, it minimizes power usage during the idle period (30 seconds by default), extends battery life, and enhances energy efficiency. The device can wake up at precise intervals, perform sensor readings, and quickly return to deep sleep, ensuring accurate scheduling and long-lasting battery performance. This makes it ideal for remote and battery-powered applications.

```c++
#define ENABLE_DEEP_SLEEP 1
```
