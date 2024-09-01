#ifndef IMU_SERVICE_HPP
#define IMU_SERVICE_HPP

#include "../../lib/network/service/comm_service.hpp"
#include "../../lib/network/service_network.hpp"
#include "../../lib/network/global/global.hpp"
#include "../model/hardware/hardware_imu.hpp"
#include "HardwareSerial.h"
/*
 * @author: Haktan Serdar Genç
 * @date: 28.07.24
 * @file: imu  service.
 */

class ImuService : public CommService
{
private: // constant
  Package *p;
  Device *device = Global::getInstance().device;

  ImuHardware *imuHardware0;

public:
  ImuService(uint8_t group, uint8_t id) : CommService(group, id)
  {
    GatewayService::getInstance().subscribeService(this);
    imuHardware0 = new ImuHardware(); // pin tanımı şuanlık rastgele
  }
  void service() override {};

  void handle(Package *package) override {

  };

  void response(String data) override {};

  ~ImuService() {}
};

#endif // IMU_SERVICE_HPP
