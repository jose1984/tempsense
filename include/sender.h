/* 
 *  sender.h
 *  
 *  Temperature sensor sender with ESP8266 and BMP180 battery-powered.
 *  
 *  @author: jose1984
 *  @version: 0.0.0
 *  @license MIT
 */

#ifndef TEMPSENSE_SENDER_H
#define TEMPSENSE_SENDER_H

#include <ESP8266HTTPClient.h>

namespace jose1984::sender
{
    class Sender
    {
    public:
        /**
         * @brief Constructor for the Sender class.
         *
         * @param server_url The URL of the server to which the measurements will be sent.
         * @param ip The local IP address of the device sending the measurements.
         * @param mac The MAC address of the device sending the measurements.
         */
        explicit Sender(const String server_url, const IPAddress ip, const String mac);

        /**
         * @brief Send measurements to the server and retrieve the sleep duration in seconds.
         *
         * @param temperature The temperature value to be sent to the server.
         * @param pressure The pressure value to be sent to the server.
         * @return uint64_t The sleep duration in seconds received from the server as a response.
         *         If the server does not respond with a valid sleep duration, the default value (0) is returned.
         */
        uint64_t sendMeasurements(const float &temperature, const float &pressure);

    private:
        const String m_server_url;
        const IPAddress m_ip;
        const String m_mac;
    };
}

#endif
