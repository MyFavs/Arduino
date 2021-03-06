#ifndef Sensors_h
#define Sensors_h

#include <Ultrasonic_V1.0.h>

class InternalSensors
{
    int _detectorLeft;
    int _detectorRight;

    int _scanState;

    Ultrasonic _uSonic1;
    Ultrasonic _uSonic2;

    int _duckySonicSensor = 0;
    bool useDuckySensor = true;


    bool ultraSonicInRange(int value)
    {
        return (UltrasonicDistance1 > 100 && UltrasonicDistance1 < 300);
    }

  public:
    InternalSensors() {}

    bool Enabled = true;

    int ULTRASONIC_LEFT = 1;
    int ULTRASONIC_RIGHT = 2;

    int DETECTOR_LEFT = 4;
    int DETECTOR_RIGHT = 8;

    int UltrasonicDistance1 = 0;
    int UltrasonicDistance2 = 0;

    


    unsigned long Time;
    
    void InitializeUltrasonicPins(int trigPin1, int echoPin1, int trigPin2, int echoPin2)
    {
        _uSonic1.Initialize(trigPin1, echoPin1);    
        _uSonic2.Initialize(trigPin2, echoPin2); 
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
        if (!Enabled)
          return;
      
        if (Time % 100 != 0)
        {
            return;
        }

        _scanState = 0;
        if (useDuckySensor)
        {
            UltrasonicDistance1 = _duckySonicSensor;
            UltrasonicDistance2 = _duckySonicSensor;
        }
        else
        {
            UltrasonicDistance1 = _uSonic1.Scan();
            UltrasonicDistance2 = _uSonic2.Scan();
        }




        if (ultraSonicInRange(UltrasonicDistance1))
        {
            _scanState += 1;
        }

        if (ultraSonicInRange(UltrasonicDistance2))
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

    void SetDuckySensor(bool value)
    {
        if (value)
        {
            _duckySonicSensor = 200;
            return;
        }
        _duckySonicSensor = 0;
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
