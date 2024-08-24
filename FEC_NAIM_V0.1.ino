
#include "HardwareSerial.h"
#include "lib/network/service/comm_service.hpp"
#include "lib/network/service/network/service_network.hpp"
#include "lib/network/global/global.hpp"
#include "lib/network/service/network/sub_uart.hpp"
#include "src/service/service_example.hpp"

NetworkService *network = &NetworkService::getInstance();
Device *device = Global::getInstance().device;
UartService *uart;

ExampleService *exampleService;

void setup()
{

  uart = new UartService(0, 115200);
  uint8_t ch = ChannelManager::getInstance().add(uart);

  RoutingTable::getInstance().add(new Route(ch, Device(3, 1, "raspberry")));

  network->monitorRoutes();
  network->monitorChannels();

  exampleService = new ExampleService();
  exampleService->service();

  // uart->write("data");
  
}

void loop()
{
  NetworkService::getInstance().listen();
}
