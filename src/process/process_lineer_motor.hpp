#include "Arduino.h"
#include <ProcessScheduler.h>
#include "service_lineer_motor.hpp"

/*
 * @author: Mustafa BICER
 * @date: 17.07.24
 * @descpription: lineer actuator service.
 * @file: process_lineer_motor.hpp
 */

class LineerMotorProcess : public Process
{
private:
  LineerMotorService *lineerMotorService = LineerMotorService::getInstance();

public:
  // Call the Process constructor
  LineerMotorProcess(Scheduler &manager, ProcPriority pr, unsigned int period, int iterations)
      : Process(manager, pr, period, iterations)
  {
  }

protected:
  virtual void service()
  {
    lineerMotorService->service(); //  run motor service
  }

  virtual void setup()
  {
    lineerMotorService->setup();
  }

  virtual void onEnable()
  {
  }

  virtual void onDisable()
  {
  }
};

/*
packet:  {"host":"raspberry","sender":"line-opt","service":1,"data":"1"} data=1 ~ 0
*/