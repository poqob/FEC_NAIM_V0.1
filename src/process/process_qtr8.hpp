#if !defined(PROCESS_QTR8_HPP)
#define PROCESS_QTR8_HPP

#include "WString.h"
#include "HardwareSerial.h"
#include <ProcessScheduler.h>
#include "../service/service_qtr.hpp"

class QTR8Process : public Process
{
private:
    ServiceQtr *service_qtr8;

public:
    // Call the Process constructor
    QTR8Process(Scheduler &manager, ProcPriority pr, unsigned int period, int iterations)
        : Process(manager, pr, period, iterations) {}

protected:
    // Create our service routine
    virtual void service()
    {
        service_qtr8->service();
    }

    virtual void setup()
    {
        service_qtr8 = new ServiceQtr(3, 3);
    }

    virtual void onEnable() {}

    virtual void onDisable() {}
};

#endif // PROCESS_QTR8_HPP
