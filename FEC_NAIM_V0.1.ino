#include "src/process/process_network.hpp"
#include "src/process/process_debug.hpp"
#include "src/process/process_mz80.hpp"
#include "src/process/process_distance.hpp"
#include "src/process/process_load.hpp"
#include "src/process/process_imu.hpp"
#include "src/process/process_lift.hpp"
#include "src/process/process_motor.hpp"

Scheduler sched;

NetworkProcess pnetwork(sched, HIGH_PRIORITY, 80, RUNTIME_FOREVER);
DebugProcess pdebug(sched, HIGH_PRIORITY, 100, RUNTIME_FOREVER);
MZ80DistanceProcess pmz(sched, HIGH_PRIORITY, 220, RUNTIME_FOREVER);
DistanceProcess pdistance(sched, HIGH_PRIORITY, 110, RUNTIME_FOREVER);
LoadProcess pload(sched, HIGH_PRIORITY, 180, RUNTIME_FOREVER);
IMUProcess pimu(sched, HIGH_PRIORITY, 100, RUNTIME_FOREVER);
LiftProcess plift(sched, HIGH_PRIORITY, 200, RUNTIME_FOREVER);
MotorProcess pmotor(sched, HIGH_PRIORITY, 120, RUNTIME_FOREVER);

void setup()
{
  pnetwork.add(true);
  pdebug.add(true);
  pmotor.add(true);
  plift.add(true);
  pdistance.add(true);
  pload.add(true);
  pimu.add(true);
}

void loop()
{
  sched.run();
}