#ifndef Command_Move_h   // If Class is not defined, then define it and use underlying code (Double Usage)
#define Command_Move_h

#include "AutomatedGuidedVehicle.h"

// #include "Command_Dodge.h"
// #include "Command_Move.h"
// #include "Command_MoveForward.h"
// #include "Command_Rotate.h"

class Command_Move
{
    int direction = 0;
    int state = 0;

    AutomatedGuidedVehicle vehicle;
    // Command_MoveForward vehicle.cmd_MoveForward1;
    // Command_Dodge vehicle.cmd_Dodge;
    // Command_Rotate vehicle.cmd_Rotate;

    public:

        Command_Move() {}


        Command_Move(AutomatedGuidedVehicle obj)
        {
            vehicle = obj;

        }

        void Update()
        {
            
            // vehicle.cmd_Rotate.Update();
            // vehicle.cmd_Dodge.Update();
            // vehicle.cmd_MoveForward1.Update();
        }

        void Start()
        {
            state = 1;
            direction = -1;
        }

        // void Forward()
        // {
        //     vehicle.cmd_MoveForward.Start();
        // }

        // void RotateLeft()
        // {
        //     vehicle.cmd_Rotate.Left();
        // }

        // void RotateRight()
        // {
        //     vehicle.cmd_Rotate.Right();
        // }

        // void Dodge()
        // {
        //     vehicle.cmd_Dodge.Start();
        // }

        bool IsFinished()
        {
            return (state == 0);
        }

        Initialize(AutomatedGuidedVehicle obj)
        {
            vehicle = obj;
        }
};

#endif // Command_Move_h