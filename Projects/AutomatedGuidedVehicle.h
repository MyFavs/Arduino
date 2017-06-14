#ifndef AutomatedGuidedVehicle_h
#define AutomatedGuidedVehicle_h

#include "arduino.h"
#include <BipolarStepper_V1.1.0.h>
#include <MotorDC_V2.0.0.h>
#include <Sensors.h>

class AutomatedGuidedVehicle
{
    // int _buttonLeft;
    // int _buttonRight;

    bool _onMat = false;
    bool _turning = false;
    bool _dodging = false;
    bool _objectDetected = false;
    bool _hitWall = false;
    bool _isMovingToMat = false;
    bool _hasMovedToMat = false;
    bool _goOnMat = false;
    bool _onMat = false;

    unsigned long _time =  millis();

    const int _rotatingSpeed = 8;
    const int _movingSpeed = 8;

    BipolarStepper _stepper;
    MotorDC _motor;

    void movingToMat()
    {
        if (_time % 300 != 0)
        {
            return;
        }

        if (Sensors.IsDetected())
        {   
            _isMovingToMat = false;
            _hasMovedToMat = true;
            GoOnMat();
        }
    }

    void goOnMat()
    {
        if (_time % 300 != 0)
        {
            return;
        }

        // ImU detection z- axis

        if (!_motor.IsMoving())
        {
            _goOnMat = false;
            _onMat = true;
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

        if (Sensors.IsDetected())
        {
            _hitWall = true;
            Stop();
            return;
        }

        if (Sensors.IsDetectedRight() || (startTurnAngle + 90 == IMU.GetCurrentRotation()))
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

  public:
    // Constructor

    int DetectDistance = 150;

    AutomatedGuidedVehicle() {}

    AutomatedGuidedVehicle()
    {
    }

    // -------------------------------------------------
    // -- Properties
    //--------------------------------------------------

    InternalSensors Sensors;

    // -------------------------------------------------
    // -- Commands
    // -------------------------------------------------

    void Forward(int moveTime)
    {
        _motor.Rotate(_movingSpeed, moveTime);
    }

    void Backward(int moveTime)
    {
        _motor.Rotate(_movingSpeed, moveTime);
    }

    // void Dodge()
    // {

    // }

    // void TurnAround()
    // {

    // }

    void TurnRight(int degree)
    {
        _stepper.Rotate(degree, _rotatingSpeed);
    }

    void TurnLeft(int degree)
    {
        _stepper.Rotate(-degree, _rotatingSpeed);
    }

    void InitializeStepper(int pin1, int pin2, int pin3, int pin4)
    {
        _stepper.Initalize(pin1, pin2, pin3, pin4);
    }

    void InitalizeMotor(int RPWM, int LPWM)
    {
        _motor.Initalize(RPWM, LPWM);
    }



    // void InitalizeButtons(int pinLeft, int pinRight)
    // {
    //     pinMode(pinLeft, INPUT);
    //     _buttonLeft = pinLeft;
    //     pinMode(pinRight, INPUT);
    //     _buttonRight = pinRight;
    // }

    bool IsMoving()
    {
        return _motor.IsMoving();
    }

    bool IsDodging()
    {
        return _dodging;
    }

    bool IsTurning()
    {
        return (_stepper.IsRotating() != 0);
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

    void HasMovedOnMat()
    {
        return _onMat;
    }

    void MoveToMat()
    {
        _isMovingToMat = true;
        _hasMovedToMat = false;
        _onMat = false;
        _goOnMat = false;
        _motor.Rotate(8);
    }

    void GoOnMat()
    {
        if (_hasMovedToMat)
        {
            _motor.Rotate(8, 3000);
            _goOnMat = true;
        }
    }


    void Update()
    {
        Sensors.Update();

// -- Moving AGV to and on the mat

        if (_isMovingToMat)
        {
            movingToMat();
        }

        if (_goOnMat)
        {
            goOnMat();
        }

// -------------------------------------

        _motor.Update();
        _stepper.Update();
    }

    void SetTime(unsigned long _updateTime)
    {
        _time = updateTime;
        Sensors.SetTime(_time);
        _motor.SetTime(_time);
        _stepper.SetTime(_time);
    }
};

#endif   // AutomatedGuidedVehicle_h