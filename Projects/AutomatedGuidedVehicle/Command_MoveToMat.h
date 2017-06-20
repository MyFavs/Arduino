#ifndef Command_MoveToMat_h   // If Class is not defined, then define it and use underlying code (Double Usage)
#define Command_MoveToMat_h

#include "AutomatedGuidedVehicle.h"

class Command_MoveToMat
{
    int state = 0;
    AutomatedGuidedVehicle *vehicle;

    public:

        Command_MoveToMat() {}

        Command_MoveToMat(AutomatedGuidedVehicle *obj)
        {
            vehicle = obj;
        }

        void Update()
        {
            if (state == 0)
                return;

            if (vehicle->Time % 100 != 0)
                return;
                
            switch(state)
            {
                case 1:
                    if (!vehicle->IsMoving())
                        vehicle->Forward(60000);

                    if (vehicle->Sensors.IsGroundDetected())
                        state++;
                    break;
                case 2:
//                    if (vehicle->IMU.IsLevel())
//                    {
//                        vehicle->Stop();
//                        state = 0;
//                    }
                    break;
            }
        }

        bool IsFinished()
        {
            return (state == 0);
        }

        void Start()
        {
            if (!IsFinished()) 
                state = 1;
        }
};

#endif // Command_MoveToMat_h
