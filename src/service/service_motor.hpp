#include "Arduino.h"
#include "HardwareSerial.h"
#ifndef MOTOR_SERVICE_HPP
#define MOTOR_SERVICE_HPP

#include <WString.h>
#include "model_packet.hpp"
class MotorService {
private:  // fields
  Packet packet;
  bool newPackage;
  
  String data;

  
public:             // methods
  void service() {  // proceed by process management system.
    // do motor things and interact with model motor.
    if (newPackage) {
      data= packet.getBody();
      //TODO: PARSE STRING
      // run PID




















      Serial.println(data); // DELETE PRINT
      newPackage = !newPackage;
    }
  }

// PIN SETUP
void setup(){
  
}

















// COMMUNUCATION
  bool receivePackage(Packet packet) {
    this->packet = Packet(packet);
    newPackage = true;
    return newPackage;
  }

// SINGLETON ARCHITECTURE
private:
  static MotorService* instance;
  MotorService() {
    newPackage=false;
    // motor_l=Motor(11);
    // motor_r=Motor(12);
  }

public:
  static MotorService* getInstance() {
    if (instance == nullptr) {
      instance = new MotorService();
    }
    return instance;
  }

  ~MotorService() = default;
  MotorService(const MotorService&) = delete;
  MotorService& operator=(const MotorService&) = delete;
};
MotorService* MotorService::instance = nullptr;

/*
packet: {"hst":"ard","sender":"rasp","service":0,"data":"00000011"}
*/

#endif  // MOTOR_SERVICE_HPP
