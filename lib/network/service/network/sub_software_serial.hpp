#ifndef SUB_SOFTWARE_SERIAL_HPP
#define SUB_SOFTWARE_SERIAL_HPP
#include "../../../network/model/channel.hpp"
#include <stdint.h>
#include <SoftwareSerial.h>
/*
 * @author: Mustafa BICER
 * @date: 21.08.24
 * @file: software serial communication option.
 */

class SoftwareSerialService : public Channel
{
private:
    SoftwareSerial serial;

public:
    SoftwareSerialService(uint8_t tx, uint8_t rx, long baud) : Channel(), serial(tx, rx)
    {
        serial.begin(baud);
    } // custom pin setup.

    // Override the read method to read incoming data from the serial port
    String read() override
    {
        String result = "";
        if (serial.available())
        {                                  // Check if data is available to read
            result += (char)serial.read(); // Read each character and append to result
        }
        return result; // Return the complete string of received data
    }

    // Override the write method to send data through the software serial
    void write(String data) override
    {
        serial.println(data); // Send data via SoftwareSerial (can also use .write() for binary data)
    }
};

#endif