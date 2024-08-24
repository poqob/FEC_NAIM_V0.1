#include "Arduino.h"
#include <ProcessScheduler.h>
#include "service_motor.hpp"

class MotorProcess : public Process {
private:
  MotorService* motorService = MotorService::getInstance();

public:
  // Call the Process constructor
  MotorProcess(Scheduler &manager, ProcPriority pr, unsigned int period, int iterations)
    : Process(manager, pr, period, iterations) {
  }

protected:
  virtual void service() {
    motorService->service(); //  run motor service
  }

  virtual void setup() {
    motorService->setup(); // pin setup
  }

  virtual void onEnable() {
  }

  virtual void onDisable() {
  }
};