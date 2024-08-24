#ifndef GLOBAL_HPP
#define GLOBAL_HPP
#include <stdint.h>
#include "../../network/model/device.hpp"
/*
 * @author: Mustafa BICER
 * @date: 20.08.24
 * @file: global variables for network
 */

struct PackageConstraints
{
  uint8_t subnet_bit_count = 3;
  uint8_t device_address_bit_count = 5;
  uint8_t service_category_bit_count = 3;
  uint8_t service_bit_count = 5;
};

struct PackageStatics
{
  uint8_t last_device = 31;
  uint8_t last_subnet = 3;
  uint8_t last_service_group = 3;
  uint8_t last_service = 31;
};

class Global
{
public:
  Device *device;
  PackageConstraints packageConstraints;
  PackageStatics packageStatics;

public:
  static Global &getInstance()
  {
    static Global instance;
    return instance;
  }

private:
  Global() {}
};
#endif