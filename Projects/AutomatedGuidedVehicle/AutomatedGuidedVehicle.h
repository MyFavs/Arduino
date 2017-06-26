#ifndef AutomatedGuidedVehicle_h
#define AutomatedGuidedVehicle_h

#include "arduino.h"
#include <BipolarStepper_V1.1.h>
#include <MotorDC_V2.0.h>
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
        Serial.println("Vehicle.Stop");
        _motor.Stop();
    }

    void Step(int steps, int spd)
    {
        _stepper.Step(steps, spd);  
    }


    void Forward(int moveTime, int moveSpeed)
    {
        Serial.print("Vehicle.Forward  Duration=");
        Serial.print(moveTime);
        Serial.print("ms  Speed=");        
        Serial.println(moveSpeed);
        _motor.Rotate(moveSpeed, moveTime);
    }

    void Forward(int moveTime)
    {
        Forward(moveTime, _movingSpeed);
    }



    void Backward(int moveTime, int moveSpeed)
    {
        Serial.print("Vehicle.Backward  Duration=");
        Serial.print(moveTime);
        Serial.print("ms  Speed=");        
        Serial.println(moveSpeed);
        _motor.Rotate(-_movingSpeed, moveTime);
    }

    void Backward(int moveTime)
    {
        Backward(moveTime, _movingSpeed);
    }


    void TurnRight(int degree, int spd)
    {
        Serial.print("Vehicle.TurnRight  Degrees=");
        Serial.print(degree);
        Serial.print("  Speed=");
        Serial.println(spd);
        _stepper.Rotate(degree, spd);
    }


    void TurnRight(int degree)
    {
        TurnRight(degree, _rotatingSpeed);
    }

    
    void TurnLeft(int degree, int spd)
    {
        Serial.print("Vehicle.TurnLeft  Degrees=");
        Serial.print(degree);
        Serial.print("  Speed=");
        Serial.println(spd);
        _stepper.Rotate(-degree, spd);
    }

    void TurnLeft(int degree)
    {
        TurnLeft(degree, _rotatingSpeed);
    }
    

    void InitializeStepper(int pin1, int pin2, int pin3, int pin4)
    {
        _stepper.Initialize(pin1, pin2, pin3, pin4);
    }

    void InitializeMotor(int RPWM, int LPWM)
    {
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
