#include "WString.h"
#include "HardwareSerial.h"
#include <ProcessScheduler.h>
#include "service_mz80.hpp"

class MZ80DistanceProcess : public Process {

public:
  Mz80Service service_mz80;

  // Call the Process constructor
  MZ80DistanceProcess(Scheduler &manager, ProcPriority pr, unsigned int period, int iterations)
    : Process(manager, pr, period, iterations) {
       service_mz80 = Mz80Service();
  }


protected:
  // Create our service routine
  virtual void service() {
    service_mz80.service();
  }

  virtual void setup() {
   
  }

  virtual void onEnable() {
  }

  virtual void onDisable() {
  }
};

// TODO: problem is we are not able to apply custom delay.