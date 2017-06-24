#ifndef Command_Rotate_h   // If Class is not defined, then define it and use underlying code (Double Usage)
#define Command_Rotate_h

#include "AutomatedGuidedVehicle.h"

class Command_Rotate
{
    int state = 0;
    int direction = 0;
    AutomatedGuidedVehicle *vehicle;

    bool yes = false;

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
                    if (!vehicle->IsMoving() && !yes)
                    {
                        Serial.println("Status is 1!!!!!");
                        vehicle->Backward(1000);
                        yes = true;
                    }

                    if (!vehicle->IsMoving())
                    {
                        state++;
                        yes = false;
                    }
                    break;

                case 2:     // 2) draai links/rechts 90 graden
                    if (!vehicle->IsTurning() && !yes)
                    {
                        Serial.println("Status is 2!!!!!");
                        switch(direction)
                        {
                            case -1:
                                vehicle->TurnLeft(70);
                                break;
                            case 1:
                                vehicle->TurnRight(70);
                                break;
                        }
                        yes = true;
                    }

                    if (!vehicle->IsTurning())
                    {
                        state++;
                        yes = false;
                    }
                    break;
                case 3:     // 3) vooruit tot 90 graden gedraaid AGV (controle IMU) & controle einde mat
                    if (!vehicle->IsMoving() && !yes)
                    {
                      Serial.println("MOVING INDEFINITELY ROTATE");
                        vehicle->Forward(30000, 3);
                        vehicle->IMU.ResetZ();
                        yes = true;
                    }
                   if (vehicle->IMU.TotalRotationZ >= 85 || vehicle->IMU.TotalRotationZ <= -85)
                   {
                       Serial.println("STOPPED ROTATING");
                       vehicle->IMU.ResetZ();
                       vehicle->Stop();
                       state++;
                       yes = false;
                   }
                    break;
                case 4:     // 4) draai links/rechts 90 graden terug
                    if (!vehicle->IsTurning() && !yes)
                    {
                        switch(direction)
                        {
                            case -1:
                                vehicle->TurnRight(70);
                                break;
                            case 1:
                                vehicle->TurnLeft(70);
                                break;
                        }
                        yes = true;
                    }

                    if (!vehicle->IsTurning())
                    {
                        state = 0;
                        yes = false;
                    }
                    break;
            }
        }

        void Left()
        {
            if (vehicle->IsMoving())
            {
                Serial.println("RotateLeft Rejected!!!");
                return;
            }
            direction = -1;
            state = 1;
        }

        void Right()
        {
            if (vehicle->IsMoving())
            {
                Serial.println("RotateRight Rejected!!!");
                return;
            }
            direction = 1;
            state = 1;
        }

        bool IsFinished()
        {
            return (state == 0);
        }

        void Stop()
        {
            direction = 0;
            state = 0;
            vehicle->Stop();
        }
};

#endif //Command_Rotate_h
