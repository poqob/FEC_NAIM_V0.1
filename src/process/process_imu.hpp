#if !defined(PROCESS_IMU_HPP)
#define PROCESS_IMU_HPP

/*
 * @author: Mustafa BICER
 * @date: 25.08.24
 * @file: process_imu.hpp
 * @description: This is a IMU process that listens to the hardware mp6050.
 */

#include "WString.h"
#include "HardwareSerial.h"
#include <ProcessScheduler.h>
#include "../../src/service/service_imu.hpp"

class IMUProcess : public Process
{
private:
  ImuService *imuService = ImuService(1, 2);

public:
  // Call the Process constructor
  IMUProcess(Scheduler &manager, ProcPriority pr, unsigned int period, int iterations)
      : Process(manager, pr, period, iterations) {}

protected:
  // Create our service routine
  virtual void service()
  {
    imuService->service(); //  run imu service
  }

  virtual void setup()
  {
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

// TODO: problem is we are not able to apply custom delay.

#endif // PROCESS_IMU_HPP
