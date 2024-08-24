#include "WString.h"
#include "HardwareSerial.h"
#include <ProcessScheduler.h>
#include "service_distance.hpp"

class DistanceProcess : public Process {

public:
DistanceService distanceService;
DistanceService distanceService0;
DistanceService distanceService1;
DistanceService distanceService2;

public:
  // Call the Process constructor
  DistanceProcess(Scheduler &manager, ProcPriority pr, unsigned int period, int iterations)
    : Process(manager, pr, period, iterations) {
      this->distanceService= DistanceService(30,31); // trig echo
      this->distanceService0= DistanceService(32,33);
      this->distanceService1= DistanceService(34,35);
      this->distanceService2= DistanceService(36,37);
  }

protected:
  // Create our service routine
  virtual void service() {
    this->force();
  }

  virtual void setup() {
    distanceService.setup();
    distanceService0.setup();
    distanceService1.setup();
    distanceService2.setup();
  }

  virtual void force() {
    distanceService.service();
    distanceService0.service();
    distanceService1.service();
    distanceService2.service();
  }


 

  virtual void onEnable() {
  }

  virtual void onDisable() {
  }

  
};

// TODO: problem is we are not able to apply custom delay.