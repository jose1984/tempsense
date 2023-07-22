/* 
 *  main.cpp
 *  
 *  Temperature sensor sender with ESP8266 and BMP180 battery-powered.
 *  
 *  @author: jose1984
 *  @version: 0.0.0
 *  @license MIT
 */

#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFiManager.h>

#include <LittleFS.h>

#include <SFE_BMP180.h>
#include <Wire.h>

#include "config.h"
#include "sender.h"

WiFiManager wifiManager;
SFE_BMP180 bmp180;

const char *param_file = "config.json";

char server_url[255] = "";
char interval_in_seconds[10] = "30";

bool should_save_config = false;
char status;
double temp = 0;
double pressure = 0;

std::unique_ptr<jose1984::sender::Sender> sender;

void setup()
{
  Serial.begin(SERIAL_MONITOR_SPEED);
  LittleFS.begin();

  // Load previous configuration from file
  File config = LittleFS.open(param_file, "r");
  if (config)
  {
    size_t size = config.size();
    std::unique_ptr<char[]> buf(new char[size]);
    config.readBytes(buf.get(), size);
    StaticJsonDocument<CONFIG_JSON_SIZE> json;
    DeserializationError error = deserializeJson(json, buf.get());
    if (error)
    {
      Serial.print("Error: Failed to load JSON config. Reason: ");
      Serial.println(error.c_str());
    }
    else
    {
      strcpy(server_url, json["server_url"]);
      strcpy(interval_in_seconds, json["interval_in_seconds"]);
    }
    config.close();
  }

  // Setup WiFiManager
  wifiManager.setSaveConfigCallback([]()
                                    { should_save_config = true; });

  WiFiManagerParameter custom_server_url("server", "Server URL", server_url, sizeof(server_url), "type=\"url\" required");
  WiFiManagerParameter custom_interval("interval", "Interval in seconds", interval_in_seconds, sizeof(interval_in_seconds), "type=\"number\" required");
  wifiManager.addParameter(&custom_server_url);
  wifiManager.addParameter(&custom_interval);
  wifiManager.setConfigPortalTimeout(WM_CONFIG_PORTAL_TIMEOUT);

  // Connect to WiFi or enter Config Portal if not configured yet
  wifiManager.autoConnect();

  strcpy(server_url, custom_server_url.getValue());
  strcpy(interval_in_seconds, custom_interval.getValue());

  // Save configuration to file if needed
  if (should_save_config)
  {
    StaticJsonDocument<CONFIG_JSON_SIZE> json;
    json["server_url"] = server_url;
    json["interval_in_seconds"] = interval_in_seconds;

    File config = LittleFS.open(param_file, "w");
    if (config)
    {
      serializeJson(json, Serial);
      serializeJson(json, config);
      config.close();
    }
    else
    {
      Serial.println("failed to open config file for writing");
    }
  }

  if (!bmp180.begin())
  {
    Serial.println("Failed to connect to BMP180. Restarting...");
    ESP.reset();
  }

  sender = std::make_unique<jose1984::sender::Sender>(String(server_url), WiFi.localIP(), WiFi.macAddress());
}

void loop()
{
  status = bmp180.startTemperature();

  if (status != 0)
  {
    delay(status);
    if (bmp180.getTemperature(temp) == 0)
    {
      Serial.println("Error retrieving temperature measurement.");
    }
  }

  status = bmp180.startPressure(3);

  if (status != 0)
  {
    delay(status);
    if (bmp180.getPressure(pressure, temp) == 0)
    {
      Serial.println("Error retrieving pressure measurement.");
    }
  }

  uint64_t wait = atol(interval_in_seconds);
  if (strlen(server_url) > 0)
  {
    wait = sender->sendMeasurements(temp, pressure);
  }

  if (wait > 0)
  {
    Serial.printf("Entering deep-sleep mode for %llu seconds...\n", wait);

#if ENABLE_DEEP_SLEEP == 1
    uint64_t sleep_time_micro_seconds = wait * 1000000UL;
    ESP.deepSleep(sleep_time_micro_seconds);
#else
    delay(wait * 1000);
#endif
  }
}
