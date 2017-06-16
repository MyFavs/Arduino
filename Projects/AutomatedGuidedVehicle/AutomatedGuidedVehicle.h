#ifndef AutomatedGuidedVehicle_h
#define AutomatedGuidedVehicle_h

#include "arduino.h"
#include <BipolarStepper_V1.1.0.h>
#include <MotorDC_V2.0.0.h>
#include "Sensors.h"

class AutomatedGuidedVehicle
{
    unsigned long _time =  millis();

    const int _rotatingSpeed = 8;
    const int _movingSpeed = 8;

    BipolarStepper _stepper;
    MotorDC _motor;

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

        void Stop()
        {
            Motor.Stop();
        }

        void Forward(int moveTime)
        {
            _motor.Rotate(_movingSpeed, moveTime);
        }

        void Backward(int moveTime)
        {
            _motor.Rotate(_movingSpeed, moveTime);
        }

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

        bool IsMoving()
        {
            return _motor.IsMoving();
        }

        bool IsTurning()
        {
            return (_stepper.IsRotating() != 0);
        }

        void Update()
        {
            Sensors.Update();
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