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

    int ULTRASONIC_LEFT = 1;
    int ULTRASONIC_RIGHT = 2;

    int DETECTOR_LEFT = 4;
    int DETECTOR_RIGHT = 8;

    unsigned long Time;
    
    void InitializeUltrasonicPins(int LeftTrigPin, int LeftEchoPin, int RightTrigPin, int RightEchoPin)
    {
        _ultrasoonLeft.Initialize(LeftTrigPin, LeftEchoPin);    
        _ultrasoonRight.Initialize(RightTrigPin, RightEchoPin); 
    }

    void InitializeDetectorPins(int pinLeft, int pinRight)
    {
        pinMode(pinLeft, INPUT);
        _detectorLeft = pinLeft;
        pinMode(pinRight, INPUT);
        _detectorRight = pinRight;
    }

    void Update()
    {
        if (Time % 100 != 0)
        {
            return;
        }

        _scanState = 0;
        int scannedLeft = _ultrasoonLeft.Scan();
        int scannedRight = _ultrasoonRight.Scan();
        // int scannedLeft = 0;
        // int scannedRight = 0;


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

    int GetScanState()
    {
        return _scanState;
    }

    bool IsGroundDetectedLeft()
    {
        return ((_scanState & DETECTOR_LEFT) == DETECTOR_LEFT);
    }

    bool IsGroundDetectedRight()
    {
        return ((_scanState & DETECTOR_RIGHT) == DETECTOR_RIGHT);
    }

    bool IsGroundDetected()
    {
        return (IsGroundDetectedLeft() || IsGroundDetectedRight());
    }

    bool IsObjectDetectedLeft()
    {
        return ((_scanState & ULTRASONIC_LEFT) == ULTRASONIC_LEFT);
    }

    bool IsObjectDetectedRight()
    {
        return ((_scanState & ULTRASONIC_RIGHT) == ULTRASONIC_RIGHT);
    }

    bool IsObjectDetected()
    {
        return (IsObjectDetectedLeft() || IsObjectDetectedRight());
    }
};

#endif
