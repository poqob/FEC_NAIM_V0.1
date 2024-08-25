#if !defined(PROCESS_DISTANCE_SENSOR)
#define PROCESS_DISTANCE_SENSOR

/*
 * @author: Mustafa BICER
 * @date: 25.08.24
 * @file: process_distance.hpp
 * @description: This is a distance HC-SR04~05 hardware reader process.
 */

#include "WString.h"
#include "HardwareSerial.h"
#include <ProcessScheduler.h>
#include "../service/service_distance.hpp"

class DistanceProcess : public Process
{

private:
  DistanceService *dservice;

public:
  // Call the Process constructor
  DistanceProcess(Scheduler &manager, ProcPriority pr, unsigned int period, int iterations)
      : Process(manager, pr, period, iterations)
  {
  }

  // Create our service routine
  virtual void service()
  {
    dservice->service();
  }

  virtual void setup()
  {
    dservice = new DistanceService();
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

#endif // PROCESS_DISTANCE_SENSOR
