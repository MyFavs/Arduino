#include <AutomatedGuidedVehicle.h>

AutomatedGuidedVehicle vehicle;
Command_Dodge cmd_Dodge(vehicle);
Command_MoveToMat cmd_MoveToMat(vehicle);
Command_Rotate cmd_Rotate(vehicle);

int state = 0;
unsigned long _time = millis();

void setup()
{
    vehicle.SetTime(_time);
    vehicle.InitializeStepper(8, 9, 10, 11);
    vehicle.InitalizeMotor(6, 7);
    vehicle.Sensors.InitalizeUltrasonicPins(2, 4, 3, 5);
    vehicle.Sensors.InitalizeDetectorPins(40, 41);
    
//    vehicle.InitalizeButtons(42, 43, 44); // Left Turn Stepper, Right Turn Stepper, Start Process
}

bool executingMoveToMat = false;
bool executing


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
                moveToMat();
            }
            else if (vehicle.HasMovedOnMat())
            {
                state = 2;
            }
            break;
        case 2:

            break;
    }

    vehicle.Update();
    updateMoveToMat();
}

void updateMoveToMat()
{
    if (!isExecutingCommand())
    {
        return;
    }

    if (needsToMoveToMat)
    {
        vehicle.moveToMat();
    }

    if (hasMovedToMat)
    {
        vehicle.GoOnMat();
    }
}

void updateRotateLeft()
{
    if (!isExecutingCommand())
    {
        return;
    }

    if (needsToRotateLeft)
    {
        vehicle.TurnLeft();
    }
}

void updateRotateRight()
{
    if (!isExecutingCommand())
    {
        return;
    }

    if (needsToRotateRight)
    {
        vehicle.TurnRight();
    }
}

void updateDodge()
{
    if (!isExecutingCommand())
    {
        return;
    }

    if (needsToDodge)
    {
        vehicle.Dodge();
    }
}

void updateMoveForward()
{
    if (!isExecutingCommand())
    {
        return;
    }

    if (needsToMoveForward)
    {
        vehicle.Forward();
    }
}

void moveToMat()
{
    cmd_MoveToMat.Start();
}

void rotateLeft()
{
    cmd_Rotate.Left();
}

void rotateRight()
{
    cmd_Rotate.Right();
}

void dodge()
{
    cmd_Dodge.Start();
}

void moveForward()
{
    // totdat er een ding is of het einde van de mat
}

void moveBackward()
{
    
}

bool isExecutingCommand()
{
    if (vehicle.IsMoving())
    {
        return true;
    }

    if (executingMoveToMat())
    {
        return true;
    }

}

void clearAllCommands()
{
    executingMoveToMat = false;

}