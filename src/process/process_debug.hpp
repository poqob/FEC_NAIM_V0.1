#if !defined(PROCESS_DEBUG_HPP)
#define PROCESS_DEBUG_HPP

/*
 * @author: Mustafa BICER
 * @date: 25.08.24
 * @file: debug process.
 * @purpose: run this code to monitor or debug the system.
 */

#include "WString.h"
#include "HardwareSerial.h"
#include <ProcessScheduler.h>
#include "../service/service_debug.hpp"
#include "../service/service_qtr.hpp"
#include "../service/service_mz80.hpp"
#include "../service/service_motor.hpp"
#include "../service/service_load.hpp"
#include "../service/service_lift.hpp"
#include "../service/service_distance.hpp"

class DebugProcess : public Process
{
private:
    DebugService *debugService;
    DebugService *debugService0;

public:
    // Call the Process constructor
    DebugProcess(Scheduler &manager, ProcPriority pr, unsigned int period, int iterations)
        : Process(manager, pr, period, iterations) {}

protected:
    // Create our service routine
    virtual void service()
    {
        debugService0->service();
    }

    virtual void setup()
    {
        // debugService = new DebugService(1, 0);
        debugService0 = new DebugService(3, 4);
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

#endif // PROCESS_DEBUG_HPP
