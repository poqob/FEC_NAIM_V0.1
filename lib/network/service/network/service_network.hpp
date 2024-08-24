#ifndef NETWORK_SERVICE_HPP
#define NETWORK_SERVICE_HPP
#include "HardwareSerial.h"
#include "../../../network/global/global.hpp"
#include "../../../network/service/a_service.hpp"
#include "../../../network/model/package.hpp"
#include "../../../network/model/routing_table.hpp"
#include "sub_gateway.hpp"
#include "sub_channel_manager.hpp"
#include "sub_router.hpp"
/*
 * @author: Mustafa BICER
 * @date: 20.08.24
 * @file: network service.
 */

class NetworkService : public Aservice
{

private:
  Device *device = Global::getInstance().device;
  Router router = Router::getInstance();
  ChannelManager cmanager = ChannelManager::getInstance();
  RoutingTable rtable = RoutingTable::getInstance();

public:
  // Public method to access the single instance
  static NetworkService &getInstance()
  {
    static NetworkService instance;
    return instance;
  }

  ~NetworkService() {}

  void monitorChannels()
  {
    Serial.println(ChannelManager::getInstance().toString());
  }
  void monitorRoutes()
  {
    Serial.println(RoutingTable::getInstance().toString());
  }

  // network listener
  void listen()
  {
    router.listen();
  }

  void handle(Package *package)
  {
    router.routeLocally(package);
  }

  void send(Package *package)
  {
    router.route(package);
  }

private:
  NetworkService()
      : Aservice() {}
};

#endif // NETWORK_SERVICE_HPP
