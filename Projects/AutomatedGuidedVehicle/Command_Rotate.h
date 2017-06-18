#ifndef Command_Rotate_h   // If Class is not defined, then define it and use underlying code (Double Usage)
#define Command_Rotate_h

#include "AutomatedGuidedVehicle.h"

class Command_Rotate
{
    int state = 0;
    int direction = 0;
    AutomatedGuidedVehicle *vehicle;

    public:

        Command_Rotate() {}

        Command_Rotate(AutomatedGuidedVehicle *obj)
        {   
            vehicle = obj;
        }
        void Update()
        {
            switch(state)
            {
                case 1:     // 1) Achteruit 
                    if (!vehicle->IsMoving())
                    {
                        vehicle->Backward(1000);
                    }

                    if (!vehicle->IsMoving())
                    {
                        state++;
                    }
                    break;

                case 2:     // 2) draai links/rechts 90 graden
                    if (!vehicle->IsTurning())
                    {
                        switch(direction)
                        {
                            case -1:
                                vehicle->TurnLeft(90);
                                break;
                            case 1:
                                vehicle->TurnRight(90);
                                break;
                        }
                    }

                    if (!vehicle->IsTurning())
                    {
                        state++;
                    }
                    break;
                case 3:     // 3) vooruit tot 90 graden gedraaid AGV (controle IMU) & controle einde mat
                    if (!vehicle->IsMoving())
                    {
                        vehicle->Forward(60000);
                        vehicle->IMU.ResetZ();
                    }
                    if (vehicle->IMU.GetTotalRotationZ() >= 90 || vehicle->IMU.GetTotalRotationZ() <= -90)
                    {
                        vehicle->IMU.ResetZ();
                        vehicle->Stop();
                        state++;
                    }
                    break;
                case 4:     // 4) draai links/rechts 90 graden terug
                    if (!vehicle->IsTurning())
                    {
                        switch(direction)
                        {
                            case -1:
                                vehicle->TurnRight(90);
                                break;
                            case 1:
                                vehicle->TurnLeft(90);
                                break;
                        }
                    }

                    if (!vehicle->IsTurning())
                    {
                        state = 0;
                    }
                    break;
            }
        }

        void Left()
        {
            direction = -1;
            state = 1;
        }

        void Right()
        {
            direction = 1;
            state = 1;
        }

        bool IsFinished()
        {
            return (state == 0);
        }
};

#endif //Command_Rotate_h