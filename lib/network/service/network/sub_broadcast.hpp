
#ifndef SUB_SERVICE_BROADCAST_HPP
#define SUB_SERVICE_BROADCAST_HPP
#include "../../../network/model/package.hpp"
#include "../../../network/global/global.hpp"
/*
 * @author: Mustafa BICER
 * @date: 20.08.24
 * @file: network broadcast service.
 */
class BroadcastService : public Aservice
{
private:
  Global global = Global::getInstance();

public:
  // Public method to access the single instance (Singleton pattern)
  static BroadcastService &getInstance()
  {
    static BroadcastService instance;
    return instance;
  }

  // add dynamic communication channels.
  void broadcast()
  {
    Package p = build();
    Serial.println(p.getContent());
  }

private:
  // Private constructor for Singleton pattern
  BroadcastService() : Aservice() {}

  Package build()
  {
    uint8_t from = global.device->id;
    uint8_t fromSubnet = global.device->subnet;
    uint8_t fromServiceCategory = global.packageStatics.last_service_group;
    uint8_t fromService = global.packageStatics.last_service;

    uint8_t to = global.packageStatics.last_device;
    uint8_t toSubnet = global.packageStatics.last_subnet;
    uint8_t toServiceCategory = global.packageStatics.last_service_group;
    uint8_t toService = global.packageStatics.last_service;

    String data = "BROADCAST";

    // Create the package using the build method
    return Package::build(from, fromSubnet, fromServiceCategory, fromService,
                          to, toSubnet, toServiceCategory, toService, data);
  }
};

#endif // SUB_SERVICE_BROADCAST_HPP