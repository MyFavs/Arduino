#ifndef AutomatedGuidedVehicle_h
#define AutomatedGuidedVehicle_h

#include "arduino.h"
#include <BipolarStepper_V1.1.0.h>
#include <MotorDC_V2.0.0.h>
#include "Sensors.h"
#include "IMU.h"

class AutomatedGuidedVehicle
{

    int _rotatingSpeed = 6;
    int _movingSpeed = 8;

    BipolarStepper _stepper;
    MotorDC _motor;

  public:
    // Constructor

    //int DetectDistance = 150;
    InternalMeasurementUnit IMU;
    unsigned long Time;
    String Name = "AGV";

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
        Serial.println("Vehicle.Stop..");
        _motor.Stop();
    }

    void Step(int steps, int spd)
    {
        _stepper.Step(steps, spd);  
    }


    void Forward(int moveTime, int moveSpeed)
    {
        Serial.print("Vehicle.Forward..  ");
        Serial.print("At speed: ");
        Serial.println(moveSpeed);
        _motor.Rotate(moveSpeed, moveTime);
    }

    void Forward(int moveTime)
    {
        Serial.print("Vehicle.Forward ");
        Serial.print(moveTime);
        Serial.println(" ms");        
        _motor.Rotate(_movingSpeed, moveTime);
    }

    void Backward(int moveTime)
    {
        Serial.print("Vehicle.Backward ");
        Serial.print(moveTime);
        Serial.println(" ms");        
        _motor.Rotate(-_movingSpeed, moveTime);
    }

    void TurnRight(int degree)
    {
        TurnRight(degree, _rotatingSpeed);
    }

    void TurnRight(int degree, int spd)
    {
        Serial.print("Vehicle.TurnRight ");
        Serial.print(degree);
        Serial.print(" degrees, speed=");
        Serial.println(spd);
        _stepper.Rotate(degree, spd);
    }

    void TurnLeft(int degree)
    {
        TurnLeft(degree, _rotatingSpeed);
    }
    
    void TurnLeft(int degree, int spd)
    {
        Serial.print("Vehicle.TurnRight ");
        Serial.print(degree);
        Serial.print(" degrees, speed=");
        Serial.println(spd);
        _stepper.Rotate(-degree, spd);
    }

    void InitializeStepper(int pin1, int pin2, int pin3, int pin4)
    {
        Serial.println("Vehicle.InitializeStepper..");
        _stepper.Initialize(pin1, pin2, pin3, pin4);
    }

    void InitializeMotor(int RPWM, int LPWM)
    {
        Serial.println("Vehicle.InitializeMotor..");
        _motor.Initialize(RPWM, LPWM);
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
        //Time = millis();

        

        _motor.Update();
        _stepper.Update();
    }
};

#endif // AutomatedGuidedVehicle_h
