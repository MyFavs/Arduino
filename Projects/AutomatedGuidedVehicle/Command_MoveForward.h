#ifndef Command_MoveForward_h   // If Class is not defined, then define it and use underlying code (Double Usage)
#define Command_MoveForward_h

#include "AutomatedGuidedVehicle.h"

class Command_MoveForward
{
    bool move = false;
    AutomatedGuidedVehicle vehicle;

    public:

        Command_MoveForward() {}

        Initialize(AutomatedGuidedVehicle* obj)
        {
            vehicle = *obj;
        }

        void Update()
        {
            if (!(vehicle.IsMoving()) && move)
            {
                Serial.print("Moving Forward..60000..  ");
                Serial.println(vehicle.Name);
                vehicle.Forward(1000);
            }

            if (vehicle.Sensors.IsGroundDetected() || vehicle.Sensors.IsObjectDetected())
            {
                Serial.print("Sensors detected!");
                //Serial.println(vehicle.Sensors.IsGroundDetected() || vehicle.Sensors.IsObjectDetected());
                move = false;
                vehicle.Stop();
            }
        }

        void Start()
        {
            move = true;
        }

        bool IsFinished()
        {
            return (!move);
        }
};

#endif // Command_MoveForward_h