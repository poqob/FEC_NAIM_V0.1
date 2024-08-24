#include "WString.h"
#include "HardwareSerial.h"
#include <ProcessScheduler.h>
#include "service_imu.hpp"

class IMUProcess : public Process {
public:
  // Call the Process constructor
  IMUProcess(Scheduler &manager, ProcPriority pr, unsigned int period, int iterations)
    : Process(manager, pr, period, iterations) {}

protected:
  // Create our service routine
  virtual void service() {
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