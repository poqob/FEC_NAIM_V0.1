#ifndef SUB_ROUTER_HPP
#define SUB_ROUTER_HPP

#include <stdint.h>
#include "sub_gateway.hpp"
#include "sub_broadcast.hpp"
#include "sub_channel_manager.hpp"
#include "../../../network/model/routing_table.hpp"

class Router : public Aservice
{
private:
  GatewayService &gateway; // Reference to GatewayService instance
  RoutingTable &rtable;    // Reference to RoutingTable instance
  BroadcastService &bs;    // Reference to BroadcastService instance

  // Private constructor
  Router()
      : gateway(GatewayService::getInstance()),
        rtable(RoutingTable::getInstance()),
        bs(BroadcastService::getInstance()) {}

public:
  // Static method to access the singleton instance
  static Router &getInstance()
  {
    static Router instance; // Guaranteed to be created only once
    return instance;
  }

  // TODO: ROUTE PACKAGES.

  // channel id, a package came from the channel.
  // send with -1 channel id to send package local to local services.
  void routeWithChannelId(uint8_t id, Package *pkg)
  {
    Device dev = Device(pkg->from(), pkg->fromSubnet(), "");
    rtable.add(new Route(id, dev));
    if (id == 255)
      gateway.gateway(pkg);
    else
    {
      uint8_t channelId = rtable.quarry(id); // returns channel id
    }
  }

  void routeLocally(Package *pkg)
  {
    gateway.gateway(pkg);
  }

  void routeNetwork(Package *pkg)
  {
    // find target device to direct package to a channel.
    uint8_t channelId = rtable.quarry(pkg->to());
    ChannelManager::getInstance().getChannelByChannelId(channelId)->write(pkg->getContent());
    delete pkg;
  }

  void route(Package *pkg)
  {
    if (pkg->to() == Global::getInstance().device->id && pkg->toSubnet() == Global::getInstance().device->subnet)
      routeLocally(pkg);
    else
      routeNetwork(pkg);
  }

  void listen()
  {
    LinkedList<uint8_t> channelids = ChannelManager::getInstance().getChannelIds();
    Channel *channel;
    String result = "";
    for (uint8_t i = 0; i < channelids.getSize(); i++)
    {
      channel = ChannelManager::getInstance().getChannelByChannelId(i);
      result = channel->read();
      if (result != "") // route the string.
      {
        Package *p = new Package(result);
        route(p);
        delete p;
      }
      result = ""; // clear the result.
    }
  }
};

#endif
