
#ifndef CHANNEL_HPP
#define CHANNEL_HPP
#include <stdint.h>
#include "WString.h"
/*
 * @author: Mustafa BICER
 * @date: 21.08.24
 * @file: abstract channel for communication options.
 */

class Channel
{
protected:
  uint8_t channelId;

public:
  Channel(uint8_t id)
      : channelId(id) {}
  Channel()
      : channelId(0) {}
  ~Channel() {}

  virtual String read() = 0;
  virtual void write(String data) = 0;

  void setId(uint8_t id)
  {
    channelId = id;
  }

  uint8_t getId()
  {
    return channelId;
  }

  virtual String toString() = 0;
};

#endif