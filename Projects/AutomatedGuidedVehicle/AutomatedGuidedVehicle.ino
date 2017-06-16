#include "AutomatedGuidedVehicle.h"

AutomatedGuidedVehicle vehicle;
Command_Dodge cmd_Dodge(vehicle);
Command_MoveToMat cmd_MoveToMat(vehicle);
Command_Rotate cmd_Rotate(vehicle);
Command_MoveForward cmd_MoveForward(vehicle);
Command_Move cmd_Move(vehicle)


int state = -1;
unsigned long _time = millis();

void setup()
{
    vehicle.SetTime(_time);
    vehicle.InitializeStepper(8, 9, 10, 11);
    vehicle.InitalizeMotor(6, 7);
    vehicle.Sensors.InitalizeUltrasonicPins(2, 4, 3, 5);
    vehicle.Sensors.InitalizeDetectorPins(40, 41);
}

void loop()
{
    detectObject()

    switch (state)
    {
        case 0:
            delay(1000);
            state = 1;
            break;
        case 1:
            if (cmd_MoveToMat.IsFinished())
            {
                cmd_MoveToMat.Start();
            }

            if (cmd_MoveToMat.IsFinished())
            {
                state++;
            }
            cmd_MoveToMat.Update();
            break;
        case 2:
            if (cmd_Rotate.IsFinished())
            {
                rotateRight();
            }

            if (cmd_Rotate.IsFinished())
            {
                state++;
            }
            break;
        case 3:
            if (cmd_MoveForward.IsFinished())
            {
                cmd_MoveForward.Start();
            }
            if (cmd_MoveForward.IsFinished())
            {
                state++;
            }
            break;
        case 4:
            if (cmd_Rotate.IsFinished())
            {
                rotateLeft();
            }

            if (cmd_Rotate.IsFinished())
            {
                state++;
            }
            break;
        case 5:
            if (cmd_Move.IsFinished())
            {
                cmd_Move.Start();
            }

            if (cmd_Move.IsFinished())
            {
                state++;
            }
            break;
    }

    vehicle.Update();
    cmd_Dodge.Update();
    cmd_MoveForward.Update();
    cmd_Move.Update();
    cmd_Rotate.Update();

}

void moveForward()
{
    vehicle.Forward(60000);
}

void moveBackward()
{
    vehicle.Backward(60000);
}

void stop()
{
    vehicle.Stop();
}

bool isExecutingCommand()
{
    if (vehicle.IsMoving())
    {
        return true;
    }

    if (!(cmd_Dodge.IsFinished() || cmd_MoveToMat.IsFinished() || cmd_Rotate.IsFinished() || cmd_Move.IsFinished() || cmd_MoveForward.IsFinished()))
    {
        return true;
    }

    return false;
}