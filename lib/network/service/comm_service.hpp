#include <stdint.h>
#ifndef ABSTRACT_COMMUNICATION_SERVICE_HPP
#define ABSTRACT_COMMUNICATION_SERVICE_HPP
#include "a_service.hpp"
#include "../../network/model/package.hpp"
/*
 * @author: Mustafa BICER
 * @date: 20.08.24
 * @file: abstract communicatable service design.
 */

/*
NOTE: IF DERRIVED SERVICE IS STATELESS (receive packages but sends no packages.)
MAKE GROUP = 0
MAKE ID = 0
*/

class CommService : public Aservice
{
protected:
    uint8_t group;
    uint8_t id;
    Package *receivedPackage;

public:
    CommService(uint8_t group, uint8_t id) : Aservice(), group(group), id(id) {}

    virtual ~CommService() {} // Corrected destructor

    uint8_t getId() { return id; }
    uint8_t getGroup() { return group; }

    virtual void service() = 0;
    virtual void handle(Package *package) = 0; // Pure virtual function
    virtual void response(String data) = 0;    // Pure virtual function
};

#endif // ABSTRACT_COMMUNICATION_SERVICE_HPP