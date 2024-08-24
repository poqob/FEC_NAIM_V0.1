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

class UartService : public Channel
{
private:
  uint8_t whichUartDoIListen;
  HardwareSerial *ser;
  String name = "uart";

public:
  UartService(uint8_t tx, uint8_t rx, long baud)
      : Channel()
  {

  } // manuel pin setup.
  // manuel serial setup.
  UartService(uint8_t serial, long baud)
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

  String read() override
  {
    String result = "";
    // Check if there is data available to read
    if (ser->available() > 0)
    {
      result = ser->readString();
      if (result.length() < 5) // +1 end char exprassion.
        return "";
    }
    return result;
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