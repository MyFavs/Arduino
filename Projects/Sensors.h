#ifndef Sensors_h
#define Sensors_h

#include <Ultrasoon_V1.0.0.h>

class InternalSensors
{   
    int _detectorLeft;
    int _detectorRight;

    int _scanState;

    Ultrasoon _ultrasoonLeft;
    Ultrasoon _ultrasoonRight;

   public:

    InternalSensors() {}

    InternalSensors()
    {
    }

    const int DETECTOR_LEFT = 4;
    const int DETECTOR_RIGHT = 8;

    void InitalizeUltrasoon(int LeftTrigPin, int LeftEchoPin, int RightTrigPin, int RightEchoPin)
    {
        _ultrasoonLeft(LeftTrigPin, LeftEchoPin);
        _ultrasoonRight(RightTrigPin, RightEchoPin);
    }

    void InitalizeDetectors(int pinLeft, int pinRight)
    {
        pinMode(pinLeft, INPUT);
        _detectorLeft = pinLeft;
        pinMode(pinRight, INPUT);
        _detectorRight = pinRight;
    }

    void Update()
    {

        _scanState = 0;
        int scannedLeft = _ultrasoonLeft.Scan();
        int scannedRight = _ultrasoonRight.Scan();

        if (scannedLeft < 300 && scannedLeft > 100)
        {
            _scanState += 1;
        }

        if (scannedRight < 300 && scannedRight > 100)
        {
            _scanState += 2;
        }

        if (digitalRead(_detectorLeft) == 0)
        {
            _scanState += 4;
        }

        if (digitalRead(_detectorRight) == 0)
        {
            _scanState += 8;
        }
    }

    void SetTime(unsigned long _updateTime)
    {
        _time = updateTime;
    }

    int GetScanState()
    {
        return _scanState;
    }

    bool IsDetectedLeft()
    {
        return (_scanState & Sensors.DETECTOR_LEFT == Sensors.DETECTOR_LEFT);
    }

    bool IsDetectedRight()
    {
        return (_scanState & Sensors.DETECTOR_RIGHT == Sensors.DETECTOR_RIGHT);
    }

    bool IsDetected()
    {
        return (IsDetectedLeft() && IsDetectedRight());
    }

};

#endif