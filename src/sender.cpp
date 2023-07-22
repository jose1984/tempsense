/* 
 *  sender.cpp
 *  
 *  Temperature sensor sender with ESP8266 and BMP180 battery-powered.
 *  
 *  @author: jose1984
 *  @version: 0.0.0
 *  @license MIT
 */

#include "sender.h"

namespace jose1984::sender
{
    Sender::Sender(const String server_url, const IPAddress ip, const String mac) : m_server_url(server_url), m_ip(ip), m_mac(mac) {}

    uint64_t Sender::sendMeasurements(const float &temperature, const float &pressure)
    {
        uint64_t wait = 0;

        WiFiClient client;
        HTTPClient httpClient;
        if (httpClient.begin(client, m_server_url.c_str()))
        {
            const String data =
                "temperature=" + String(temperature) + "&pressure=" + String(pressure) + "&ip=" + m_ip.toString() + "&mac=" + m_mac;

            httpClient.addHeader("Content-Type", "application/x-www-form-urlencoded");
            httpClient.setTimeout(60e3);
            const int httpCode = httpClient.POST(data);
            if (HTTP_CODE_OK == httpCode)
            {
                String response = httpClient.getString();
                if (response.length() > 0)
                {
                    wait = response.toInt();
                }
            }
            httpClient.end();
        }

        return wait;
    }
}