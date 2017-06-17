#ifndef IMU_h   // If Class is not defined, then define it and use underlying code (Double Usage)
#define IMU_h

#include <Wire.h>

class InternalMeasurementUnit
{
    int isLevel = false;
    long accelX, accelY, accelZ;
    float gForceX, gForceY, gForceZ;

    long gyroX, gyroY, gyroZ;
    float rotX, rotY, rotZ;

    float rot;

    unsigned long Time;

    void setupMPU()
    {
        Wire.beginTransmission(0b1101000);
        Wire.write(0x6B);
        Wire.write(0b00000000);
        Wire.endTransmission();
        Wire.beginTransmission(0b1101000);
        Wire.write(0x1B);
        Wire.write(0x00000000);
        Wire.endTransmission();
        Wire.beginTransmission(0b1101000);
        Wire.write(0x1C);
        Wire.write(0b00000000);
        Wire.endTransmission();
    }

    void recordAccelRegisters()
    {
        Wire.beginTransmission(0b1101000);
        Wire.write(0x3B);
        Wire.endTransmission();
        Wire.requestFrom(0b1101000, 6);
        while (Wire.available() < 6)
            ;
        accelX = Wire.read() << 8 | Wire.read();
        accelY = Wire.read() << 8 | Wire.read();
        accelZ = Wire.read() << 8 | Wire.read();
        processAccelData();
    }

    void processAccelData()
    {
        gForceX = accelX / 16384.0;
        gForceY = accelY / 16384.0;
        gForceZ = accelZ / 16384.0;
    }

    void recordGyroRegisters()
    {
        Wire.beginTransmission(0b1101000);
        Wire.write(0x43);
        Wire.endTransmission();
        Wire.requestFrom(0b1101000, 6);
        while (Wire.available() < 6)
            ;
        gyroX = Wire.read() << 8 | Wire.read();
        gyroY = Wire.read() << 8 | Wire.read();
        gyroZ = Wire.read() << 8 | Wire.read();
        processGyroData();
    }

    void processGyroData()
    {
        rotX = gyroX / 131.0;
        rotY = gyroY / 131.0;
        rotZ = gyroZ / 131.0;
    }

  public:
    IMU()
    {
        setupMPU();
    }

    void Update()
    {
        Time = millis();
        if (Time % 100 == 0)
        {
            recordAccelRegisters();
            recordGyroRegisters(); 
            if (rotZ > 1 || rotZ < -1)
            {
                rot = rot + rotZ / 10;
            }

            if (gForceZ > 0.9)
            {
                isLevel = true;
            }
            else
            {
                isLevel = false;
            }
        }
    }

    float GetAccelerationZ()
    {
        return gForceZ;
    }

    float GetTurnSpeedZ()
    {
        return rotZ;
    }

    float GetTotalRotationZ()
    {
        return rot;
    }

    bool IsLevel()
    {
        return isLevel;
    }

    void ResetZ()
    {
        rot = 0;
    }
};

#endif //IMU_h