#include "AutomatedGuidedVehicle.h"
#include "Command_Dodge.h"
#include "Command_Move.h"
#include "Command_MoveForward.h"
#include "Command_MoveToMat.h"
#include "Command_Rotate.h"
#include "Sensors.h"

AutomatedGuidedVehicle vehicle;

Command_Dodge cmd_Dodge(vehicle);
Command_MoveToMat cmd_MoveToMat(vehicle);
Command_Rotate cmd_Rotate(vehicle);
Command_MoveForward cmd_MoveForward(vehicle);
Command_Move cmd_Move(vehicle);

unsigned long _time = millis();
int state = -1;
bool _processing = false;

void setup()
{
    vehicle.SetTime(_time);
    vehicle.InitializeStepper(8, 9, 10, 11);
    vehicle.InitializeMotor(6, 7);
    vehicle.Sensors.InitializeUltrasonicPins(2, 4, 3, 5);
    vehicle.Sensors.InitializeDetectorPins(40, 41);
    vehicle.Sensors.InitializeRemoteControlPin(12);
    pinMode(13, OUTPUT);
}

void loop()
{
    // --------------AFSTANDSBEDIENING UITVRAGEN---------------
    if (!isExecutingCommand())
    {
        if (vehicle.Sensors.Remote.Code > 0)
        {
            String command = vehicle.Sensors.Remote.Command;
            if (command == "CH-")
            {
                digitalWrite(13, HIGH);
            }
            else
            {
                digitalWrite(13, LOW);
            }
        }
    }
    processUpdate();
    vehicle.Update();
    cmd_Dodge.Update();
    cmd_MoveForward.Update();
    cmd_Move.Update();
    cmd_Rotate.Update();
}

bool isExecutingCommand()
{
    if (vehicle.IsMoving())
    {
        return true;
    }

    if (!(cmd_Dodge.IsFinished() || cmd_MoveToMat.IsFinished() || cmd_Rotate.IsFinished() || cmd_Move.IsFinished() || cmd_MoveForward.IsFinished() || _processing))
    {
        return true;
    }

    return false;
}

void start()
{
    _processing = true;
    state = 1;
}

void processUpdate()
{
    switch (state)
    {
    case 1:
        if (cmd_MoveToMat.IsFinished())
        {
            delay(1000);
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
            cmd_Rotate.Right();
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
            cmd_Rotate.Left();
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
            state = 0;
            _processing = false;
        }
        break;
    }
}
