/* 
 *  config.h
 *  
 *  Temperature sensor sender with ESP8266 and BMP180 battery-powered.
 *  
 *  @author: jose1984
 *  @version: 0.0.0
 *  @license MIT
 */

#ifndef TEMPSENSE_CONFIG_H
#define TEMPSENSE_CONFIG_H

// Serial monitor baud rate
#define SERIAL_MONITOR_SPEED 9600

// Size of the JSON buffer used for storing configuration data
#define CONFIG_JSON_SIZE 1024

// Configuration portal timeout duration in seconds
#define WM_CONFIG_PORTAL_TIMEOUT 180

// Define ENABLE_DEEP_SLEEP to 1 to enable deep sleep, or set to 0 to disable deep sleep
// Note: RST and D0 pins need to be jumped in your ESP8266 to use deep sleep
#define ENABLE_DEEP_SLEEP 1

#endif
