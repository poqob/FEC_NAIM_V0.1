#include "Arduino.h"
#include "HardwareSerial.h"
#ifndef RECEIVER_SERVICE_HPP
#define RECEIVER_SERVICE_HPP

#include <WString.h>
#include "model_packet.hpp"
#include "service_motor.hpp"
#include "service_lineer_motor.hpp"

class ReceiverService {
private:  // fields
  Packet packet;
  MotorService* motorService = MotorService::getInstance();
  LineerMotorService* lineerMotorService = LineerMotorService::getInstance();


private:
  // direct packages to owner services.
  void gateway(Packet packet) {
    switch (packet.getService()) {
      case 0:  // motor service
        motorService->receivePackage(packet);
        break;
      case 1:
        lineerMotorService->receivePackage(packet);
        break;
      default:
        break;
    }
  }

public:
  String input = "";
  void service() {
    // do motor things and interact with model motor.
    if (Serial.available()) {
      input = Serial.readStringUntil('\n');
      Packet packet = Packet::fromJSON(input);  // parse package
      gateway(packet);                          // direct
    }
  }

private:
  static ReceiverService* instance;
  ReceiverService() {
  }

public:
  static ReceiverService* getInstance() {
    if (instance == nullptr) {
      instance = new ReceiverService();
    }
    return instance;
  }

  ~ReceiverService() = default;
  ReceiverService(const ReceiverService&) = delete;
  ReceiverService& operator=(const ReceiverService&) = delete;
};
ReceiverService* ReceiverService::instance = nullptr;

/*
packet: {"sender":"raspberry","service":0,"data":"{"x":123,"y":252}"}
*/

#endif  // RECEIVER_SERVICE_HPP
