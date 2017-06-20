#ifndef AutomatedGuidedVehicle_h
#define AutomatedGuidedVehicle_h

#include "arduino.h"
#include <BipolarStepper_V1.1.0.h>
#include <MotorDC_V2.0.0.h>
#include "Sensors.h"
//#include <IMU_V1.0.0.h>


class AutomatedGuidedVehicle
{
    

    int _rotatingSpeed = 8;
    int _movingSpeed = 8;

    BipolarStepper _stepper;
    MotorDC _motor;



  public:
    // Constructor

    int DetectDistance = 150;
    //InternalMeasurementUnit IMU;
    unsigned long Time;
    String Name = "AGV";


    AutomatedGuidedVehicle() {}

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

    void Forward(int moveTime)
    {
        Serial.println("Vehicle.Forward..");
        _motor.Rotate(_movingSpeed, moveTime);
    }

    void Backward(int moveTime)
    {
        Serial.println("Vehicle.Backward..");
        _motor.Rotate(_movingSpeed, moveTime);
    }

    void TurnRight(int degree)
    {
        Serial.println("Vehicle.TurnRight..");
        _stepper.Rotate(degree, _rotatingSpeed);
    }

    void TurnLeft(int degree)
    {
        Serial.println("Vehicle.TurnLeft..");
        _stepper.Rotate(-degree, _rotatingSpeed);
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
        
        //IMU.Update();
        
        //Sensors.Update();
        
        _motor.Update();
        _stepper.Update();
        

    } 
};

#endif // AutomatedGuidedVehicle_h
