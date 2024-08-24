
#include "model_packet.hpp"
#include "process_receiver.hpp"
#include "process_motor.hpp"
#include "process_lineer_motor.hpp"
#include "process_distance.hpp"
#include "process_mz80.hpp"
#include "process_estop.hpp"
#include "process_network.hpp"

// MANAGE EVENTS IN PROCESSES - pass the setup adjusts(like pins) into processes.
// MANAGE DATA IN SERVICES
// MANAGE EMBEDDED SYSTEMS AND I/O IN MODELS

Scheduler sched; // Create a global Scheduler object
//ReceiverProcess rp(sched, MEDIUM_PRIORITY, 500, RUNTIME_FOREVER);
NetworkProcess np(sched, MEDIUM_PRIORITY, 500, RUNTIME_FOREVER);
// MotorProcess mp(sched, MEDIUM_PRIORITY, 1000, RUNTIME_FOREVER);
// LineerMotorProcess lmp(sched, HIGH_PRIORITY, 100, RUNTIME_FOREVER);
//DistanceProcess dp(sched, MEDIUM_PRIORITY, 250, RUNTIME_FOREVER);
// MZ80DistanceProcess mz(sched, HIGH_PRIORITY, 20, RUNTIME_FOREVER);
// EmergencyStopProcess es(sched, HIGH_PRIORITY, 10, RUNTIME_FOREVER,50,52);

void setup()
{
  Serial.begin(115200);
  // Packet pkt = Packet("ard", "rasp", 0, "00000011");
  // Serial.println(pkt.serialize());
  // es.add(true);
  //rp.add(true);
  // mp.add(true);
  // lmp.add(true);
  np.add(true);
  //dp.add(true);
  // mz.add(true);
  
}

void loop()
{
  sched.run();
}
