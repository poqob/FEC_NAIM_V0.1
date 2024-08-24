#ifndef ABSTRACT_COMMUNICATION_SERVICE_HPP
#define ABSTRACT_COMMUNICATION_SERVICE_HPP
#include "a_service.hpp"
#include <stdint.h>
/*
 * @author: Mustafa BICER
 * @date: 22.08.24
 * @file: abstract hardware service design.
 */
class HardwareService : public Aservice
{
public:
    HardwareService() : Aservice() {}
    virtual ~HardwareService() {} // Corrected destructor
    virtual void service() = 0;
    virtual void setup() = 0;
};

#endif // ABSTRACT_COMMUNICATION_SERVICE_HPP