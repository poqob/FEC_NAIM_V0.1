#include "Arduino.h"
#include <ProcessScheduler.h>
#include "../../src/service/service_lift.hpp"

/*
 * @author: Mustafa BICER
 * @date: 01.09.24
 * @descpription: lift management process.
 * @file: process_lift.hpp
 */

class LiftProcess : public Process
{
private:
  LiftService *liftService = LiftService(2, 1);

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