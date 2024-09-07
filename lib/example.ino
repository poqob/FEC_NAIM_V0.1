#include "network/service/network/service_network.hpp"
#include "network/service/network/sub_channel_manager.hpp"
#include "network/service/network/sub_uart.hpp"
#include "service_dumb.hpp"
#include "service_pmud.hpp"

NetworkService *network = &NetworkService::getInstance();

Uart *uart;
DumpService *ds;
PmudService *ps;

void networkSetup()
{
  uart = new Uart(0, 115200);
  uint8_t ch = ChannelManager::getInstance().add(uart);
  RoutingTable::getInstance().add(new Route(ch, Device(3, 1, "raspberry")));
  RoutingTable::getInstance().add(new Route(ch, Device(5, 2, "win")));

  ds = new DumpService();
  ps = new PmudService();
}

void setup()
{

  networkSetup();
  network->monitorRoutes();
  network->monitorChannels();
  ds->service();
}

void service()
{
  // ds->service();
  NetworkService::getInstance().listen();
}

void loop()
{

  // ChannelManager::getInstance().send(p);
  service();
}
