#if !defined(PROCESS_DEBUG_HPP)
#define PROCESS_DEBUG_HPP

/*
 * @author: Mustafa BICER
 * @date: 5.09.24
 * @file: general process.
 * @purpose: this code is for general process.
 */

#include "WString.h"
#include "HardwareSerial.h"
#include <ProcessScheduler.h>
#include "../service/service_general.hpp"

class DebugProcess : public Process
{
private:
    GeneralService *sgeneral;

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
        sgeneral = new GeneralService(3, 5);
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
