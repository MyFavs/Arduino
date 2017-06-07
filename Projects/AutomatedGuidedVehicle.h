#ifndef AutomatedGuidedVehicle_h
#define AutomatedGuidedVehicle_h

#include "arduino.h"
#include <BipolarStepper_V1.1.0.h>
#include <MotorDC_V2.0.0.h>
#include <Ultrasoon_V1.0.0.h>

class AutomatedGuidedVehicle
{
    int _detectorLeft;
    int _detectorRight;
    int _buttonLeft;
    int _buttonRight;

    bool _onMat = false;
    bool _turning = false;
    bool _dodging = false;
    bool _objectDetected = false;
    bool _hitWall = false;
    bool _isMovingToMat = false;
    bool _hasMovedToMat = false;

    int _time = millis();

    BipolarStepper _stepper;
    MotorDC _motor;
    Ultrasoon _ultrasoonLeft;
    Ultrasoon _ultrasoonRight;

    void movingToMat()
    {
        if (_time % 300 != 0)
        {
            return;
        }

        if (detect() == 3)
        {
            if (_ultrasoonLeft.Scan() <= DetectDistance || _ultrasoonRight.Scan() <= DetectDistance)
            {
                objectDetected = true;
                Stop();
                return;
            }
            if (detectorLeft == 0 || detectorRight == 0)
            {
                onMat = true;
                if (_time % 300 == 0)
                {
                    Stop();
                    return;
                }
            }
        }
    }

    void moveLane()
    {
        Motor.Rotate(8); //------------------------> 1x aanroepen

        int startTurnAngle = IMU.GetCurrentRotation();

        Stepper.Rotate(45, 8); //------------------> 1x aanroepen

        if (_time % 300 == 0)
        {
            return;
        }

        if (detectorRight == 0 && detectorLeft == 0)
        {
            _hitWall = true;
            Stop();
            return;
        }

        if (detectorRight == 0 || (startTurnAngle + 90 == IMU.GetCurrentRotation()))
        {
            _hitWall = true;
            Stop();
            return;
        }

        if (_ultrasoonLeft.Scan() <= DetectDistance || _ultrasoonRight.Scan() <= DetectDistance)
        {
            objectDetected = true;
            Stop();
            return;
        }
    }

    void Stop()
    {
        Motor.Stop();
    }


    int detect()
    {
        int result = 0;

        if (digitalRead(_detectorLeft) == 0)
        {
            result += 1;
        }

        if (digitalRead(_detectorRight) == 0)
        {
            result += 2;
        }

        return result;
    }

  public:
    // Constructor

    int DetectDistance = 150;

    AutomatedGuidedVehicle() {}

    AutomatedGuidedVehicle()
    {
    }

    // -------------------------------------------------
    // -- Commands
    // -------------------------------------------------

    void Forward()
    {
    }

    void Dodge()
    {
    }

    void TurnAround()
    {
    }

    void InitializeStepper(int pin1, int pin2, int pin3, int pin4)
    {
        _stepper.Initalize(pin1, pin2, pin3, pin4);
    }

    void InitalizeMotor(int RPWM, int LPWM)
    {
        _motor.Initalize(RPWM, LPWM);
    }

    void InitalizeUltrasoonLeft(int TrigPin, int EchoPin)
    {
        _ultrasoonLeft(TrigPin, EchoPin);
    }

    void InitalizeUltrasoonRight(int TrigPin, int EchoPin)
    {
        _ultrasoonRight(TrigPin, EchoPin);
    }

    void InitalizeDetectors(int pinLeft, int pinRight)
    {
        pinMode(pinLeft, INPUT);
        _detectorLeft = pinLeft;
        pinMode(pinRight, INPUT);
        _detectorRight = pinRight;
    }

    void InitalizeButtons(int pinLeft, int pinRight)
    {
        pinMode(pinLeft, INPUT);
        _buttonLeft = pinLeft;
        pinMode(pinRight, INPUT);
        _buttonRight = pinRight;
    }

    bool IsMoving()
    {
        return motor.IsMoving();
    }

    bool IsDodging()
    {
        return _dodging;
    }

    bool IsTurning()
    {
        return _turning;
    }

    bool IsAtWall()
    {
        return _hitWall;
    }

    bool ObjectDetected()
    {
        return _objectDetected;
    }

    bool IsMovingToMat()
    {
        return _isMovingToMat;
    }

    void HasMovedToMat()
    {
        return _hasMovedToMat;
    }

    void MoveToMat()
    {
        _isMovingToMat = true;
        _hasMovedToMat = false;
        Motor.Rotate(8);
    }


    void Update()
    {
        if (_isMovingToMat)
        {
            movingToMat();
        }

        if ()
        {

        }
    }
};

#endif   // AutomatedGuidedVehicle_h