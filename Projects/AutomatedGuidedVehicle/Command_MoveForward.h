#ifndef Command_MoveForward_h   // If Class is not defined, then define it and use underlying code (Double Usage)
#define Command_MoveForward_h

#include "AutomatedGuidedVehicle.h"

class Command_MoveForward
{
    bool move = false;
    AutomatedGuidedVehicle *vehicle;

    public:

        Command_MoveForward() {}

        Command_MoveForward(AutomatedGuidedVehicle *obj)
        {
            // Serial.println(obj->Name);
            vehicle = obj;
            // Serial.println(vehicle->Name);
        }

        void Update()
        {
            Serial.print("IsGroundDetected: ");
            Serial.println(vehicle->Sensors.IsGroundDetected());
            if (!(vehicle->IsMoving()) && move)
            {
                // Serial.print("Moving Forward..60000..  ");
                // Serial.println(vehicle->Name);
                vehicle->Forward(30000);
            }

            if ((vehicle->Sensors.IsGroundDetected() || vehicle->Sensors.IsObjectDetected()) && move)
            {
                Serial.print("Sensors detected!");
                //Serial.println(vehicle.Sensors.IsGroundDetected() || vehicle.Sensors.IsObjectDetected());
                move = false;
                vehicle->Stop();
            }
        }

        void Start()
        {
            if (vehicle->IsMoving())
            {
                Serial.println("MoveForward Rejected!!!");
                return;
            }
            move = true;
        }

        bool IsFinished()
        {
            return (!move);
        }

        void Stop()
        {
            Serial.print("Stopped!");
            move = false;
            vehicle->Stop();
        }
};

#endif // Command_MoveForward_h