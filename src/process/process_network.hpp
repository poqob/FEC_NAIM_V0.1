#if !defined(PROCESS_NETWORK_HPP)
#define PROCESS_NETWORK_HPP

/*
 * @author: Mustafa BICER
 * @date: 25.08.24
 * @file: network process.
 * @description: This is a network process that listens to the network.
 */

#include <ProcessScheduler.h>
#include "../../lib/network/service_network.hpp"
#include "../../lib/network/service/network/sub_uart.hpp"

class NetworkProcess : public Process
{
private:
  NetworkService *nservice = &NetworkService::getInstance();

public:
  // Call the Process constructor
  NetworkProcess(Scheduler &manager, ProcPriority pr, unsigned int period, int iterations)
      : Process(manager, pr, period, iterations)
  {
  }

protected:
  // Create our service routine
  virtual void service()
  {
    nservice->listen();
  }

  virtual void setup()
  {
    Global::getInstance().device = new Device(0, 1, "uno");
    Uart *uart = new Uart(0, 115200);
    uint8_t ch = ChannelManager::getInstance().add(uart);
  }

  virtual void force()
  {
  }

  virtual void onEnable()
  {
  }

  virtual void onDisable()
  {
  }
};

// TODO: problem is we are not able to apply custom delay.

#endif // PROCESS_NETWORK_HPP
