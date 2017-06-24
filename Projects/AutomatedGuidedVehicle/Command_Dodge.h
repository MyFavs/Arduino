#ifndef Command_Dodge_h   // If Class is not defined, then define it and use underlying code (Double Usage)
#define Command_Dodge_h

#include "AutomatedGuidedVehicle.h"

class Command_Dodge
{
    int state = 0;
    AutomatedGuidedVehicle *vehicle;
    bool yes = false;

    public:

    Command_Dodge() {}

    Command_Dodge(AutomatedGuidedVehicle *obj)
    {
        vehicle = obj;
    }

    void Update()
    {
        switch(state)
        {
            case 0:
                return;
            case 1:
                vehicle->Stop();
                state++;
                break;
            // 1) Achteruit
            case 2:
                if (!vehicle->IsMoving() && !yes)
                {
                    vehicle->Backward(1000);
                    yes = true;
                }

                if (!vehicle->IsMoving())
                {
                    state++;
                    yes = false;
                }
                break;
            // 2) draai 45 graden naar links
            case 3:
                if (!vehicle->IsTurning() && !yes)
                {
                    vehicle->TurnLeft(45);
                    yes = true;
                }

                if (!vehicle->IsTurning())
                {
                    state++;
                    yes = false;
                }
                break;
            // 3) vooruit x meter (IMU)
            case 4:
                if (!vehicle->IsMoving() && !yes)
                {
                    vehicle->Forward(1000);
                    yes = true;
                }

                if (!vehicle->IsMoving())
                {
                    state++;
                    yes = false;
                }
                break;
            // 4) draai 45 graden naar rechts
            case 5:
                if (!vehicle->IsTurning() && !yes)
                {
                    vehicle->TurnRight(45);
                    yes = true;
                }

                if (!vehicle->IsTurning())
                {
                    state++;
                    yes = false;
                }
                break;
            // 5) vooruit x meter (IMU)
            case 6:
                if (!vehicle->IsMoving()  && !yes)
                {
                    vehicle->Forward(1000);
                    yes = true;
                }

                if (!vehicle->IsMoving())
                {
                    state++;
                    yes = false;
                }
                break;
            // 6) draai 45 graden naar rechts
            case 7:
                if (!vehicle->IsTurning() && !yes)
                {
                    vehicle->TurnRight(45);
                    yes = true;
                }

                if (!vehicle->IsTurning())
                {
                    state++;
                    yes = false;
                }
                break;
            // 7) vooruit x meter (IMU)
            case 8:
                if (!vehicle->IsMoving() && !yes)
                {
                    vehicle->Forward(1000);
                    yes = true;
                }

                if (!vehicle->IsMoving())
                {
                    state++;
                    yes = false;
                }
                break;
            // 8) draai 45 graden naar links
            case 9:
                if (!vehicle->IsTurning() && !yes)
                {
                    vehicle->TurnLeft(45);
                    yes = true;
                }

                if (!vehicle->IsTurning())
                {
                    state++;
                    yes = false;
                }
                break;
            // 9) vooruit x meter (IMU)
            case 10:
                if (!vehicle->IsMoving() && !yes)
                {
                    vehicle->Forward(500);
                    yes = true;
                }

                if (!vehicle->IsMoving())
                {
                    state = 0;
                    yes = false;
                }
                break;
        }
    }

    bool IsFinished()
    {
        return (state == 0);
    }

    void Start()
    {
        if (vehicle->IsMoving())
            {
                Serial.println("Dodge Rejected!!!");
                return;
            }
        if (IsFinished()) 
            state = 1;
    }

    void Stop()
        {
            state = 0;
            vehicle->Stop();
        }
};

#endif // Command_Dodge_h



