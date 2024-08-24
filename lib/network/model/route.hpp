#ifndef ROUTE_HPP
#define ROUTE_HPP
#include <stdint.h>
#include "../../network/model/device.hpp"
/*
 * @author: Mustafa BICER
 * @date: 21.08.24
 * @file: route.hpp
 */

class Route
{
public:
  uint8_t id; // channel id
  Device device;
  Route(uint8_t channelId, Device device)
      : id(channelId), device(device) {}

  String toString()
  {
    String result = "";
    result += "id:";
    result += id;
    result += " device:{";
    result += device.toString();
    result += "}";
    return result;
  }
};

#endif