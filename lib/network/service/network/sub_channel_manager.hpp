
#ifndef SUB_SERVICE_CHANNEL_MANAGER_HPP
#define SUB_SERVICE_CHANNEL_MANAGER_HPP
#include <stdint.h>
#include "../../../network/service/a_service.hpp"
#include "../../../network/model/channel.hpp"
#include "../../../network/dstructure/LinkedList.hpp"
/*
 * @author: Mustafa BICER
 * @date: 21.08.24
 * @file: channel manager.
 */

class ChannelManager : public Aservice
{
private:
  LinkedList<Channel *> channels; // stores channels.
public:
  // Public method to access the single instance (Singleton pattern)
  static ChannelManager &getInstance()
  {
    static ChannelManager instance;
    return instance;
  }

  uint8_t add(Channel *channel)
  {
    channel->setId(this->channels.getSize());
    channels.addBack(channel);
    return this->channels.getSize() - 1;
  }

  Channel *getChannelByChannelId(uint8_t id)
  {
    return channels.get(id);
  }

  LinkedList<uint8_t> getChannelIds()
  {
    LinkedList<uint8_t> channelids;
    for (uint8_t i = 0; i < channels.getSize(); i++)
      channelids.addBack(channels.get(i)->getId());
    return channelids;
  }

  String toString()
  {
    String result = "";
    for (uint8_t i = 0; i < channels.getSize(); i++)
      result += channels.get(i)->toString() + "\n";
    return result;
  }

private:
  // Private constructor for Singleton pattern
  ChannelManager()
      : Aservice()
  {
    // Initialization code
  }
};

#endif // SUB_SERVICE_GATEWAY_HPP