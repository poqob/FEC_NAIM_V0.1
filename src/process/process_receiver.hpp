#include "HardwareSerial.h"
#include "Arduino.h"
#include <ProcessScheduler.h>
#include "model_packet.hpp"
#include "service_receiver.hpp"

// TODO:create service_receiver
class ReceiverProcess : public Process {

private://fields
 ReceiverService* receiverService = ReceiverService::getInstance();



public:
  // Call the Process constructor
  ReceiverProcess(Scheduler &manager, ProcPriority pr, unsigned int period, int iterations)
    : Process(manager, pr, period, iterations) {
  }

protected:
  // Create our service routine
  virtual void service() {
    receiverService->service();
  }

  virtual void setup() {
  }

  virtual void onEnable() {
    Serial.println("process receiver up."); // WRITE STATUS CLASS TO NOTIFY THESE INTO CONSOLE. 
  }

  virtual void onDisable() {
    Serial.println("process receiver up.");
  }
};

/*
valid orders.
{"sender":"raspberry","service":0,"data":"{x:100,y:253}"}

*/





