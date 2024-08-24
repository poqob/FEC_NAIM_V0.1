
#include "HardwareSerial.h"
#include "lib/network/service/comm_service.hpp"
#include "lib/network/service/network/service_network.hpp"
#include "lib/network/global/global.hpp"
#include "lib/network/service/network/sub_uart.hpp"
#include "src/service/service_example.hpp"
#include "src/service/service_motor.hpp"
#include "src/service/service_distance.hpp"
#include "src/service/service_mz80.hpp"

NetworkService *network = &NetworkService::getInstance();
DistanceService *distanceService;
Mz80Service *mz80Service;
ExampleService *exampleService;
MotorService *motorService;

void setup()
{
  Global::getInstance().device = new Device(0, 1, "uno");
  UartService *uart = new UartService(0, 115200);
  uint8_t ch = ChannelManager::getInstance().add(uart);

  // network->monitorRoutes();
  // network->monitorChannels();

  exampleService = new ExampleService();
  motorService = new MotorService();

  distanceService = new DistanceService();
  mz80Service = new Mz80Service();
}

void loop()
{
  delay(85);
  // mz80Service->service();
  distanceService->service(); // TODO:process
  NetworkService::getInstance().listen();
}
