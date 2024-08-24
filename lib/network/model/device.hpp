#ifndef DEVICE_HPP
#define DEVICE_HPP
#include "WString.h"
#include <stdint.h>
/*
* @author: Mustafa BICER
* @date: 21.08.24
* @file: device.hpp 
*/
class Device {
public:
  uint8_t id;
  uint8_t subnet;
  String name;
public:
  Device() {}
  Device(uint8_t id,
         uint8_t subnet,
         String name) {
    this->name = name;
    this->id = id;
    this->subnet = subnet;
  }

  String toString(){
    String result="";
    result+="id:";
    result+=id;
    result+=" subnet:";
    result+=subnet;
    result+=" name:";
    result+=name;
    return result;
  }
};
#endif