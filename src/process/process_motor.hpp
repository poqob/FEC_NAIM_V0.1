#include "Arduino.h"
#include <ProcessScheduler.h>
#include "../service/service_motor.hpp"

/*
 * @author: Mustafa BICER
 * @date: 25.08.24
 * @file: process_motor.hpp
 * @description: This is a motor process that handles network packages to the motor.
 */

class MotorProcess : public Process
{
private:
  MotorService *motorService;

public:
  // Call the Process constructor
  MotorProcess(Scheduler &manager, ProcPriority pr, unsigned int period, int iterations)
      : Process(manager, pr, period, iterations)
  {
    motorService = new MotorService();
  }

protected:
  virtual void service()
  {
    motorService->service(); //  run motor service
  }

  virtual void setup()
  {
  }

  virtual void onEnable()
  {
  }

  virtual void onDisable()
  {
  }
};