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
    String result = ChannelManager::getInstance().toString();
    if (result.length() == 0)
      Serial.println("No routes found.");
    else
      Serial.println(result);
  }
  void monitorRoutes()
  {
    String result = RoutingTable::getInstance().toString();
    if (result.length() == 0)
      Serial.println("No routes found.");
    else
      Serial.println(result);
  }

  void monitorLocalServices()
  {
    String result = String(GatewayService::getInstance().serviceCount());
    if (result.length() == 0)
      Serial.println("No routes found.");
    else
      Serial.println(result);
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
