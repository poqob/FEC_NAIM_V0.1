#if !defined(PROCESS_MZ80_HPP)
#define PROCESS_MZ80_HPP

#include "WString.h"
#include "HardwareSerial.h"
#include <ProcessScheduler.h>
#include "../service/service_mz80.hpp"

class MZ80DistanceProcess : public Process
{
private:
  Mz80Service *service_mz80;

public:
  // Call the Process constructor
  MZ80DistanceProcess(Scheduler &manager, ProcPriority pr, unsigned int period, int iterations)
      : Process(manager, pr, period, iterations) {}

protected:
  // Create our service routine
  virtual void service()
  {
    service_mz80->service();
  }

  virtual void setup()
  {
    service_mz80 = new Mz80Service();
  }

  virtual void onEnable() {}

  virtual void onDisable() {}
};

// TODO: problem is we are not able to apply custom delay.

#endif // PROCESS_MZ80_HPP
