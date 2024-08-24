#ifndef IMU_SERVICE_HPP
#define IMU_SERVICE_HPP
#include "HardwareSerial.h"

/*
 * @author: Mustafa BICER
 * @date: 17.07.24
 * @file: IMU service.
 */

class ImuService
{

public:
  float velocity()
  {
    return 0.0;
  }

  ImuService()
  {
  }

  ~ImuService() {}
};
#endif // IMU_SERVICE_HPP
