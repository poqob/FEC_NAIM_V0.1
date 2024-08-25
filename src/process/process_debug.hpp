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

class DebugProcess : public Process
{
private:
    DebugService *exampleService;

public:
    // Call the Process constructor
    DebugProcess(Scheduler &manager, ProcPriority pr, unsigned int period, int iterations)
        : Process(manager, pr, period, iterations) {}

protected:
    // Create our service routine
    virtual void service()
    {
    }

    virtual void setup()
    {
        exampleService = new DebugService();
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
