#include <AutomatedGuidedVehicle.h>

AutomatedGuidedVehicle vehicle;

int state = 0;

void setup()
{
    vehicle.InitializeStepper(8, 9, 10, 11);
    vehicle.InitalizeMotor(6, 7);
    vehicle.InitalizeUltrasoonLeft(2, 4);
    vehicle.InitalizeUltrasoonRight(3, 5);
    vehicle.InitalizeDetectors(40, 41);
    vehicle.InitalizeButtons(42, 43, 44); // Left Turn Stepper, Right Turn Stepper, Start Process
}

void loop()
{
    switch (state)
    {
        case 0:
            if (vehicle.IsStartButtonPressed)
            {
                delay(1000);
                state = 1;
            }
            break;
        case 1:
            if (!vehicle.IsMovingToMat())
            {
                vehicle.MoveToMat();
            }
            else if (vehicle.HasMovedToMat())
            {
                state = 2;
            }
            break;
        case 2:
            if (vehicle.HasMovedToMat())
            {
                
            }
            break;
    }

    vehicle.Update();
}