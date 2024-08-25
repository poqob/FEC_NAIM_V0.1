
#ifndef LINEER_MOTOR_SERVICE_HPP
#define LINEER_MOTOR_SERVICE_HPP

#include "Arduino.h"
#include "HardwareSerial.h"
#include <WString.h>

/*
 * @author: Mustafa BICER
 * @date: 17.07.24
 * @file: lineer actuator service.
 */

class LineerMotorService
{
private: // fields
  bool newPackage;
  bool mzListen;

  unsigned long timer = 0;
  unsigned long kapanma_sure = 12000;

  // PACKET DESIGN PATTERN
private:
  void sendPackage() {}
  String parse()
  {
    return this->packet.getBody();
  }

public:
  bool receivePackage(Packet packet)
  {
    this->packet = Packet(packet);
    newPackage = true;
    return newPackage;
  }

  // PROCESS DESIGN PATTERN
public:
  void service()
  {
    }

  void setup()
  {

    // pinMode(lineerMotor.r_en, OUTPUT);
    // pinMode(lineerMotor.l_en, OUTPUT);
    // pinMode(lineerMotor.r_pwm, OUTPUT);
    // pinMode(lineerMotor.l_pwm, OUTPUT);
  }

  // **************EMBEDDED SYSTEM DESIGN PATTERN**************
private:
  void on()
  {
    // digitalWrite(lineerMotor.r_en, HIGH);
    // digitalWrite(lineerMotor.l_en, HIGH);
    // analogWrite(lineerMotor.r_pwm, 0);
    // analogWrite(lineerMotor.l_pwm, 255);
    timer = 0;
    Serial.println("Motor on");
  }

  void off()
  {
    if (timer == 0)
    {
      timer = millis();
    }

    if (millis() - timer < kapanma_sure)
    {
      // digitalWrite(lineerMotor.r_en, HIGH);
      // digitalWrite(lineerMotor.l_en, HIGH);
      // analogWrite(lineerMotor.r_pwm, 255);
      // analogWrite(lineerMotor.l_pwm, 0);
    }
    else
    {
      // digitalWrite(lineerMotor.r_en, LOW);
      // digitalWrite(lineerMotor.l_en, LOW);
      // analogWrite(lineerMotor.r_pwm, 0);
      // analogWrite(lineerMotor.l_pwm, 0);
      timer = 0;
    }
    Serial.println("Motor off");
  }

  void stop()
  {
    // digitalWrite(this->lineerMotor.r_en, LOW);
    // digitalWrite(this->lineerMotor.l_en, LOW);
    // analogWrite(this->lineerMotor.r_pwm, 0);
    // analogWrite(this->lineerMotor.l_pwm, 0);
  }

  /*
  *************SINGLETON DESIGN PATTERN*************
  */
private:
  static LineerMotorService *instance;
  LineerMotorService()
  {
    newPackage = false;
    mzListen = true;
    // lineerMotor = LineerMotor();
    // lineerMotor.setPins();
  }

public:
  static LineerMotorService *getInstance()
  {
    if (instance == nullptr)
    {
      instance = new LineerMotorService();
    }
    return instance;
  }

  ~LineerMotorService() = default;
  LineerMotorService(const LineerMotorService &) = delete;
  LineerMotorService &operator=(const LineerMotorService &) = delete;
};
LineerMotorService *LineerMotorService::instance = nullptr;

/*
packet: {"hst":"ard","sender":"mz","service":1,"data":"0"} data=1 ~ 0
{"hst":"ard","sender":"rasp","service":1,"data":"0"}
*/

#endif // LINEER_MOTOR_SERVICE_HPP
