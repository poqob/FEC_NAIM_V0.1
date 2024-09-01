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
  LiftService *liftService;

public:
  // Call the Process constructor
  LiftProcess(Scheduler &manager, ProcPriority pr, unsigned int period, int iterations)
      : Process(manager, pr, period, iterations)
  {
  }

protected:
  virtual void service()
  {
    liftService->service(); //  run motor service
  }

  virtual void setup()
  {
    liftService = new LiftService(2, 1);
  }

  virtual void onEnable()
  {
  }

  virtual void onDisable()
  {
  }
};
