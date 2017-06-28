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


    void Move(int spd, int moveTime)
    {
        if (spd == 0)
            return;

        if (spd > 0)
            Serial.print("Vehicle.Move(Forward)  Duration=");
        else 
            Serial.print("Vehicle.Move(Backward)  Duration=");

        Serial.print(moveTime);
        Serial.print("ms  Speed=");        
        Serial.println(spd);
        _motor.Rotate(spd, moveTime);
    }


    void Turn(int degree, int spd)
    {
        Serial.print("Vehicle.Turn  Degrees=");
        Serial.print(degree);
        Serial.print("  Speed=");
        Serial.println(spd);
        _stepper.Rotate(degree, spd);
    }


    void Turn(int degree)
    {
        Turn(degree, _rotatingSpeed);
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
