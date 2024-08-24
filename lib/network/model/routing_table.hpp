

#ifndef ROUTING_TABLE_HPP
#define ROUTING_TABLE_HPP
#include "WString.h"
#include <stdint.h>
#include "../../network/dstructure/LinkedList.hpp"
#include "../../network/model/route.hpp"
/*
 * @author: Mustafa BICER
 * @date: 21.08.24
 * @file: routing table.
 */
class RoutingTable
{
private:
  LinkedList<Route *> routes; // List of routes

  // Private constructor to prevent external instantiation
  RoutingTable() {}

public:
  // Public static method to access the singleton instance
  static RoutingTable &getInstance()
  {
    static RoutingTable instance; // Guaranteed to be created only once
    return instance;
  }

  void add(Route *route)
  {
    if (quarry(route->device.id) == 255)
      routes.addBack(route);
  }

  // Returns channel ID, or 255 if not found (to indicate invalid ID)
  uint8_t quarry(uint8_t deviceId)
  {
    if (routes.isEmpty())
      return 255;

    for (int i = 0; i < routes.getSize(); i++)
    {
      Route *r = routes.get(i);
      if (r->device.id == deviceId)
        return r->id; // channel id
    }
    return 255; // Return 255 if deviceId not found
  }

  String toString()
  {
    String result = "";
    for (int i = 0; i < routes.getSize(); i++)
    {
      result += routes.get(i)->toString(); // Assuming your Route class has a toString() method
    }
    return result;
  }
};

#endif
