
#ifndef SUB_SERVICE_GATEWAY_HPP
#define SUB_SERVICE_GATEWAY_HPP
#include "../../../network/model/package.hpp"
#include "../../../network/service/comm_service.hpp"
#include "../../../network/dstructure/LinkedList.hpp"

/*
 * @author: Mustafa BICER
 * @date: 20.08.24
 * @file: network gateway service.
 */

class GatewayService : public Aservice
{
private:
  LinkedList<Aservice *> slist; // Updated to hold pointers

public:
  // Public method to access the single instance (Singleton pattern)
  static GatewayService &getInstance()
  {
    static GatewayService instance;
    return instance;
  }

  void subscribeService(CommService *comservice)
  { // Pass by pointer
    slist.addBack(comservice);
  }

  void gateway(Package *package)
  {
    for (int i = 0; i < slist.getSize(); i++)
    {
      CommService *s = static_cast<CommService *>(slist.get(i));
      if (s->getId() == package->toService())
        s->handle(package);
    }
  }

private:
  // Private constructor for Singleton pattern
  GatewayService()
      : Aservice()
  {
    // Initialization code
  }
};

#endif // SUB_SERVICE_GATEWAY_HPP