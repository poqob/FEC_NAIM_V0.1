#ifndef SUB_UART_HPP
#define SUB_UART_HPP
#include "WString.h"
#include <stdint.h>
#include "HardwareSerial.h"
#include "../../../network/model/channel.hpp"

/*
 * @author: Mustafa BICER
 * @date: 21.08.24
 * @file: uart communication option.
 */

class Uart : public Channel
{

private:
  // byte numChars = 32;
  // char receivedChars[numChars];
  // bool newData = false;

private:
  uint8_t whichUartDoIListen;
  HardwareSerial *ser;
  String name = "uart";

public:
  Uart(uint8_t tx, uint8_t rx, long baud)
      : Channel()
  {

  } // manuel pin setup.
  // manuel serial setup.
  Uart(uint8_t serial, long baud)
      : Channel()
  {

    switch (serial)
    {
    case 0:
      ser = &Serial;
      break;
      /* case 1:
      ser = &Serial1;
      break;
    case 2:
      ser = &Serial2;
      break;*/
    default:
      ser = &Serial; // Fallback to Serial
      name += serial;
      break;
    }
    ser->begin(baud); // Initialize the selected serial port
  }

  // HardwareSerial *ser= &Serial;
  // String read() override
  // {
  //   String result = "";
  //   // Check if there is data available to read
  //   if (ser->available() > 0)
  //   {
  //     result = ser->readString();
  //     // cclear buffer
  //     if (result.length() < 5) // +1 end char exprassion.
  //       return "";
  //   }
  //   return result;
  // }

  // optimum message: "  $ 0101" optimum buffer size: 10
  // optimum message: "14characters" optimum buffer size: 16

  String read() override
  {
    // Set a fixed buffer size and read limit
    const int bufferSize = 16;
    char buffer[bufferSize];
    int bytesRead = 0;
    memset(buffer, 0, sizeof(buffer));
    // Check if there is data available to read
    if (ser->available() > 0)
    {
      ser->setTimeout(100);
      bytesRead = ser->readBytes(buffer, bufferSize - 1); // Read bytes into buffer

      buffer[bytesRead] = '\0'; // Null-terminate the buffer

      if (bytesRead < 5) // If too short, discard the data
      {
        return "";
      }
      return String(buffer); // Convert buffer to String only if needed
    }
    return "";
  }

  void write(String data) override
  {
    // if (ser->available())
    ser->println(data);
  }

  String toString() override
  {
    String result = "";
    result += "id:";
    result += channelId;
    result += " name:";
    result += name;
    return result;
  }
};

#endif