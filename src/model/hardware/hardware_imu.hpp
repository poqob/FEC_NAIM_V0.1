#ifndef IMU_HARDWARE_HPP
#define IMU_HARDWARE_HPP

#include "../../../lib/network/service/hardware_service.hpp"
#include "HardwareSerial.h"

#include <Wire.h>

/*
 * @author: Harun Yeşilyurt
 * @date: 28.08.24
 * @file: imu service.
 */
class ImuHardware : public HardwareService
{
private:
  // Jiroskop ve ivmeölçer verileri için değişkenler
  float RateRoll, RatePitch, RateYaw;
  float RateCalibrationRoll, RateCalibrationPitch, RateCalibrationYaw;
  int RateCalibrationNumber;
  float AccX, AccY, AccZ;
  float Roll = 0, Pitch = 0, Yaw = 0;
  float LastRoll = 0, LastPitch = 0, LastYaw = 0;
  uint32_t LoopTimer;
  const float THRESHOLD = 20.0;                     // Değişim eşiği
  const unsigned long CALIBRATION_DURATION = 10000; // Kalibrasyon süresi (10 saniye)
  unsigned long lastCalibrationTime = 0;            // Son kalibrasyon zamanı
  unsigned long setupStartTime = 0;                 // Setup başlangıç zamanı

  // Jiroskop verisini °/s cinsinden ölçeklendirmek için dönüşüm faktörü
  const float GYRO_SCALE_FACTOR = 65.5;

public:
  ImuHardware()
  {
  }

  ~ImuHardware() {}

  void setup()
  {
    Wire.setClock(400000); // I2C saat hızını ayarla
    Wire.begin();          // I2C haberleşmesini başlat

    // delay(250) yerine geçen kod
    setupStartTime = millis();
    while (millis() - setupStartTime < 250)
    {
      // 250 ms boyunca bekle
    }

    // MPU9250'yi başlat
    Wire.beginTransmission(0x68);
    Wire.write(0x6B);
    Wire.write(0x00);
    Wire.endTransmission();

    // Jiroskop kalibrasyonu için değerleri topla
    for (RateCalibrationNumber = 0; RateCalibrationNumber < 2000; RateCalibrationNumber++)
    {
      gyro_signals();
      RateCalibrationRoll += RateRoll;
      RateCalibrationPitch += RatePitch;
      RateCalibrationYaw += RateYaw;
    }

    // Ortalama kalibrasyon değerlerini hesapla
    RateCalibrationRoll /= 2000;
    RateCalibrationPitch /= 2000;
    RateCalibrationYaw /= 2000;

    LoopTimer = micros();           // Döngü zamanlayıcısını başlat
    lastCalibrationTime = millis(); // Başlangıç zamanı
  }
  void service()
  {
    gyro_signals(); // Jiroskop ve ivmeölçer verilerini oku

    // Kalibrasyon değerlerini çıkart
    RateRoll -= RateCalibrationRoll;
    RatePitch -= RateCalibrationPitch;
    RateYaw -= RateCalibrationYaw;

    // Roll, Pitch ve Yaw açılarını hesapla
    Roll += RateRoll * 0.006;   // 0.012 saniye döngü süresi
    Pitch += RatePitch * 0.006; // 0.012 saniye döngü süresi
    Yaw += RateYaw * 0.006;     // 0.012 saniye döngü süresi

    // Yaw açısını 0 ile 360 derece arasında tut
    if (Yaw < 0)
    {
      Yaw += 360;
    }
    else if (Yaw >= 360)
    {
      Yaw -= 360;
    }

    unsigned long currentTime = millis();

    // 10 saniye içinde değerlerin değişimini kontrol et
    if (currentTime - lastCalibrationTime >= CALIBRATION_DURATION)
    {
      float yawChange = abs(Yaw - LastYaw);

      // Eşik değerinin altında değişim varsa, açıları sıfırla
      if (yawChange < THRESHOLD)
      {
        // Yaw açısını en yakın referans açıya yuvarla
        if (abs(Yaw - 0) <= 45)
        {
          Yaw = 0;
        }
        else if (abs(Yaw - 90) <= 45)
        {
          Yaw = 90;
        }
        else if (abs(Yaw - 180) <= 45)
        {
          Yaw = 180;
        }
        else if (abs(Yaw - 270) <= 45)
        {
          Yaw = 270;
        }
        else if (abs(Yaw - 360) <= 45 || abs(Yaw) <= 45)
        {
          Yaw = 360;
        }

        // Serial.println("Yaw angle calibrated to nearest reference point.");
      }

      // Son değerleri güncelle
      LastRoll = Roll;
      LastPitch = Pitch;
      LastYaw = Yaw;
      lastCalibrationTime = currentTime; // Kalibrasyon zamanı güncelle
    }

    // Açıları seri port üzerinden yazdır
    Serial.print("Roll Angle [°]: ");
    Serial.print(Roll);
    Serial.print(" Pitch Angle [°]: ");
    Serial.print(Pitch);
    Serial.print(" Yaw Angle [°]: ");
    Serial.println(Yaw);

    // Döngü süresini ayarla
    while (micros() - LoopTimer < 4000)
      ;
    LoopTimer = micros();
  }

private:
  // Kalman filtresi fonksiyonu
  void kalman_1d(float &KalmanState, float &KalmanUncertainty, float KalmanInput, float KalmanMeasurement)
  {
    KalmanState = KalmanState + 0.004 * KalmanInput;
    KalmanUncertainty = KalmanUncertainty + 0.004 * 0.004 * 4 * 4;
    float KalmanGain = KalmanUncertainty * 1 / (1 * KalmanUncertainty + 3 * 3);
    KalmanState = KalmanState + KalmanGain * (KalmanMeasurement - KalmanState);
    KalmanUncertainty = (1 - KalmanGain) * KalmanUncertainty;
  }

  // Jiroskop ve ivmeölçer verilerini oku ve işle
  void gyro_signals(void)
  {
    // MPU9250'deki bazı register ayarlarını yap
    Wire.beginTransmission(0x68); // I2C adresi
    Wire.write(0x1A);             // Register adresi
    Wire.write(0x05);             // Ayar değeri
    Wire.endTransmission();

    Wire.beginTransmission(0x68);
    Wire.write(0x1C);
    Wire.write(0x10);
    Wire.endTransmission();

    // İvmeölçer verilerini oku
    Wire.beginTransmission(0x68);
    Wire.write(0x3B); // İvmeölçer verilerinin başladığı register adresi
    Wire.endTransmission();
    Wire.requestFrom(0x68, 6);
    int16_t AccXLSB = Wire.read() << 8 | Wire.read();
    int16_t AccYLSB = Wire.read() << 8 | Wire.read();
    int16_t AccZLSB = Wire.read() << 8 | Wire.read();

    // Jiroskop verilerini oku
    Wire.beginTransmission(0x68);
    Wire.write(0x1B);
    Wire.write(0x8);
    Wire.endTransmission();

    Wire.beginTransmission(0x68);
    Wire.write(0x43); // Jiroskop verilerinin başladığı register adresi
    Wire.endTransmission();
    Wire.requestFrom(0x68, 6);
    int16_t GyroX = Wire.read() << 8 | Wire.read();
    int16_t GyroY = Wire.read() << 8 | Wire.read();
    int16_t GyroZ = Wire.read() << 8 | Wire.read();

    // Jiroskop verilerini dönüştür
    RateRoll = (float)GyroX / GYRO_SCALE_FACTOR;
    RatePitch = (float)GyroY / GYRO_SCALE_FACTOR;
    RateYaw = (float)GyroZ / GYRO_SCALE_FACTOR;

    // İvmeölçer verilerini dönüştür
    AccX = (float)AccXLSB / 4096;
    AccY = (float)AccYLSB / 4096;
    AccZ = (float)AccZLSB / 4096;
  }
};

#endif // IMU_HARDWARE_HPP
