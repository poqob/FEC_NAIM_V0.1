#ifndef DISTANCE_HARDWARE_HPP
#define DISTANCE_HARDWARE_HPP

#include "../../../lib/network/service/hardware_service.hpp"
#include "HardwareSerial.h"

/*
 * @author: Haktan Serdar Genç
 * @date: 24.08.24
 * @file: motor service.
 */
class DistanceHardware : public HardwareService
{
private:
  uint8_t trigPin;
  uint8_t echoPin;
  float distance;
  long duration;

  unsigned long previousMillis = 0;
  int interval = 1000;
  unsigned long triggerStartMillis = 0;
  unsigned long triggerHighMillis = 0;
  bool triggered = false;
  bool measuring = false;

public:
  String service()
  {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval)
    {
      previousMillis = currentMillis;
      digitalWrite(trigPin, LOW);
      triggerStartMillis = currentMillis;
      triggered = true;
      measuring = false;
    }

    if (triggered && (currentMillis - triggerStartMillis >= 5))
    {
      digitalWrite(trigPin, HIGH);
      triggerHighMillis = currentMillis;
      triggered = false;
      measuring = true;
    }

    if (measuring && (currentMillis - triggerHighMillis >= 10))
    {
      digitalWrite(trigPin, LOW);
      measuring = false;

      duration = pulseIn(echoPin, HIGH);
      distance = (duration / 29.1) / 2;
    }

    return String(distance);
  }

  DistanceHardware(uint8_t trigPin, uint8_t echoPin)
      : HardwareService(), trigPin(trigPin), echoPin(echoPin)
  {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
  }

  ~DistanceHardware() {}
};
#endif // DISTANCE_HARDWARE_HPP