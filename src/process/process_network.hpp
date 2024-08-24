#include "Arduino.h"
#include <ProcessScheduler.h>
#include "service_network.hpp"
class NetworkProcess : public Process {
private:
NetworkService nservice=NetworkService::getInstance();

public:
  // Call the Process constructor
  NetworkProcess(Scheduler &manager, ProcPriority pr, unsigned int period, int iterations)
    : Process(manager, pr, period, iterations) {
  }

protected:
  // Create our service routine
  virtual void service() {
    nservice.service();
  }

  virtual void setup() {
  }

  virtual void force() {
  }

  virtual void onEnable() {
  }

  virtual void onDisable() {
  }
};

// TODO: problem is we are not able to apply custom delay.