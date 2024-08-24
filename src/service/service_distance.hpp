#include <stdint.h>

#ifndef DISTANCE_SERVICE_HPP
#define DISTANCE_SERVICE_HPP

#include "Arduino.h"
#include "HardwareSerial.h"
#include <WString.h>


class DistanceService {

private:
  uint8_t trigPin;
  uint8_t echoPin;
  float distance;
  long duration;


  unsigned long previousMillis = 0;  // Stores the last time the action was taken
   int interval = 1000;        // Interval at which to repeat the action (milliseconds)
  unsigned long triggerStartMillis = 0;
  unsigned long triggerHighMillis = 0;
  bool triggered = false;
  bool measuring = false;
public:


  void setup() {
    pinMode(this->trigPin, OUTPUT);
    pinMode(this->echoPin, INPUT);
  }


   void service() {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      // Start the trigger pulse
      digitalWrite(trigPin, LOW);
      triggerStartMillis = currentMillis;
      triggered = true;
      measuring = false;
    }

    if (triggered && (currentMillis - triggerStartMillis >= 5)) {
      // Set the trigPin to HIGH for 10 microseconds
      digitalWrite(trigPin, HIGH);
      triggerHighMillis = currentMillis;
      triggered = false;
      measuring = true;
    }

    if (measuring && (currentMillis - triggerHighMillis >= 10)) {
      // Set the trigPin back to LOW and start measuring
      digitalWrite(trigPin, LOW);
      measuring = false;

      duration = pulseIn(echoPin, HIGH);
      distance = (duration / 29.1) / 2;
    }
    Serial.print(trigPin);
    Serial.print(":");
    Serial.println(distance);
  }

  DistanceService(uint8_t trigPin, uint8_t echoPin) {
    this->echoPin = echoPin;
    this->trigPin = trigPin;
  }

  DistanceService(){}

  ~DistanceService() {}
  //DistanceService& DistanceService::operator=(const DistanceService&);
};
#endif  // DISTANCE_SERVICE_HPP
