#include "Arduino.h"
#include <ProcessScheduler.h>
#include "../../src/service/service_load.hpp"

/*
 * @author: Mustafa BICER
 * @date: 01.09.24
 * @descpription: load sensor management.
 * @file: process_load.hpp
 */

class LoadProcess : public Process
{
private:
    LoadService *loadService = LoadService(2, 2);

public:
    // Call the Process constructor
    LoadProcess(Scheduler &manager, ProcPriority pr, unsigned int period, int iterations)
        : Process(manager, pr, period, iterations)
    {
    }

protected:
    virtual void service()
    {
        loadService->service(); //  run motor service
    }

    virtual void setup()
    {
        loadService->setup();
    }

    virtual void onEnable()
    {
    }

    virtual void onDisable()
    {
    }
};

/*
packet:  {"host":"raspberry","sender":"line-opt","service":1,"data":"1"} data=1 ~ 0
*/