#include "src/process/process_network.hpp"
#include "src/process/process_debug.hpp"
#include "src/process/process_mz80.hpp"
#include "src/process/process_distance.hpp"

Scheduler sched;

NetworkProcess np(sched, HIGH_PRIORITY, 50, RUNTIME_FOREVER);
DebugProcess dep(sched, MEDIUM_PRIORITY, 50, RUNTIME_FOREVER);
MZ80DistanceProcess mp(sched, MEDIUM_PRIORITY, 50, RUNTIME_FOREVER);
DistanceProcess dp(sched, HIGH_PRIORITY, 80, RUNTIME_FOREVER);

void setup()
{
  np.add(true);
  dep.add(true);
  // mp.add(true);
  // dp.add(true);
}

void loop()
{
  sched.run();
}