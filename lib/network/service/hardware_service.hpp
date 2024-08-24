#ifndef HARDWARE_SERVICE_HPP
#define HARDWARE_SERVICE_HPP
#include "a_service.hpp"
#include "Arduino.h"
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
};

#endif // HARDWARE_SERVICE_HPP