#ifndef Commands_h // If Class is not defined, then define it and use underlying code (Double Usage)
#define Commands_h

#include "AutomatedGuidedVehicle.h"

class Command
{
    bool busy = false;
    int state = 0;
    String command = "";
    int turnradius = 0;

    AutomatedGuidedVehicle *vehicle;
    

    void printState(String value)
    {
        Serial.print(">STEP ");
        Serial.print(state);
        Serial.print(":");
        Serial.println(value);
    }

    void finished()
    {
        Serial.print("# Finished Command: ");
        Serial.println(command);
        Serial.println("-----------------------------------");
        command = "";
        turnradius = 0;
        state = 0;
        busy = false;
    }

// --------------------------  EXECUTE -------------------------------


    void execute(String value)
    {
        Serial.print("# Executing Command: ");
        Serial.println(value);
        if (vehicle->IsMoving() || busy)
        {
            Serial.println(value);
            Serial.println(" Rejected!!!");
            return;
        }
        if (IsFinished())
        {
            command = value;
            state = 1;
        }
    }


    void execute_Backward()
    {
        if (!vehicle->IsMoving() && !busy)
        {
            printState("BACKING UP");
            vehicle->Backward(1000,1);
            busy = true;
        }

        if (!vehicle->IsMoving())
        {
            state++;
            busy = false;
        }
    }

    void execute_Forward()
    {
        if (!vehicle->IsMoving() && !busy)
        {
            printState("FAST FORWARD");
            vehicle->Forward(2000, 8);
            busy = true;
        }

        if (!vehicle->IsMoving())
        {
            state++;
            busy = false;
        }
    }

    void execute_MoveTillAreaDetected()
    {
        if (!vehicle->IsMoving() && !busy)
        {
            printState("MOVE FORWARD");
            vehicle->Forward(0, 2);
            vehicle->IMU.ResetZ();
            busy = true;
        }
       if (!vehicle->Sensors.IsGroundDetected())
       {
           printState("AREA DETECTED");
           vehicle->Stop();
           state++;
           busy = false;
       }          
    }    

    void execute_MoveTillGroundDetected()
    {
        if (!vehicle->IsMoving() && !busy)
        {
            printState("MOVE FORWARD");
            vehicle->Forward(0, 2);
            vehicle->IMU.ResetZ();
            busy = true;
        }
        if (vehicle->Sensors.IsGroundDetected())
        {
            printState("GROUND DETECTED");
            vehicle->Stop();
            state++;
            busy = false;
        }
    }



    void execute_MoveTillRotationReached(int value)
    {
        int rot = value;
        if (rot < 0)
        {
            rot = -rot;
        }
        if (!vehicle->IsMoving() && !busy)
        {
            printState("MOVE FORWARD");
            vehicle->Forward(0, 3);
            vehicle->IMU.ResetZ();
            busy = true;
        }
       if (vehicle->IMU.TotalRotationZ >= rot || vehicle->IMU.TotalRotationZ <= -rot)
       {
           printState("ROTATION REACHED");
           vehicle->IMU.ResetZ();
           vehicle->Stop();
           state++;
           busy = false;
       }          
    }

    // void execute_TurnLeft(int value)
    // {
    //     execute_Turn(value, -1);
    // }

    // void execute_TurnRight(int value)
    // {
    //     execute_Turn(value, 1);
    // }

    
    void execute_Turn(int value)
    {
        int dir = 1;
        if (value < 0)
            dir = -1;

        if (!vehicle->IsTurning() && !busy)
        {
            switch(dir)
            {
                case -1:
                    printState("STEER LEFT");
                    vehicle->TurnLeft(-value);
                    break;
                case 1:
                    printState("STEER RIGHT");
                    vehicle->TurnRight(value);
                    break;
            }
            busy = true;
        }

        if (!vehicle->IsTurning())
        {
            state++;
            busy = false;
        }
    }







// --------------------------  UPDATE -------------------------------



    void update_Forward()
    {
        switch (state)
        {
            case 1: // Voorruit totdat grond gedetecteerd is
                execute_Forward();
                break;

            case 2: // Voorruit totdat grond gedetecteerd is
                execute_MoveTillGroundDetected();
                break;

            default:
                finished();
                break;
        }
    }
    void update_Backward()
    {
        switch (state)
        {
            case 1: // Voorruit totdat grond gedetecteerd is
                execute_Backward();
                break;

            default:
                finished();
                break;
        }
    }

    void update_Dodge()
    {
        switch (state)
        {
            //  Achteruit
            case 1:
                execute_Backward();
                break;
            case 2: // draai links 90 graden
                execute_Turn(-35);
                break;
            case 3: // vooruit tot x graden gedraaid AGV (controle IMU) & controle einde mat
                execute_MoveTillRotationReached(35);
                break;
            case 4: // draai rechts 90 graden
                execute_Turn(70);
                break;
            case 5: // vooruit tot x graden gedraaid AGV (controle IMU) & controle einde mat
                execute_MoveTillRotationReached(70);
                break;
            case 6: // draai links 90 graden
                execute_Turn(-70);
                break;
            case 7: // vooruit tot x graden gedraaid AGV (controle IMU) & controle einde mat
                execute_MoveTillRotationReached(35);
                break;
            case 8: // draai rechts 45 graden
                execute_Turn(35);
                break;
            default:
                finished();
                break;
        }
    }

    void update_MoveToArea()
    {
        switch (state)
        {
            case 1: // Voorruit totdat grond gedetecteerd is
                execute_MoveTillAreaDetected();
                break;

            default:
                finished();
                break;
        }
    }


    // void update_TurnArround()
    // {
    //     switch (state)
    //     {
    //         case 1: // Achteruit
    //             execute_Backward();
    //             break;
    //         case 2: // draai links
    //             execute_TurnLeft(45);
    //             break;
    //         case 3: // vooruit tot x graden gedraaid AGV (controle IMU) & controle einde mat
    //             execute_MoveTillRotationReached(180);
    //             break;
    //         case 4: // draai rechts
    //             execute_TurnRight(45);
    //             break;

    //         default:
    //             finished();
    //             break;
    //     }
    // }


    void update_Turn()
    {
        switch (state)
        {
            case 1: // Achteruit
                execute_Backward();
                break;
            case 2: // draai links
                if (turnradius < 0)
                    execute_Turn(-45);
                else
                    execute_Turn(45);
                break;
            case 3: // vooruit tot x graden gedraaid AGV (controle IMU) & controle einde mat
                execute_MoveTillRotationReached(turnradius);
                break;
            case 4: // draai rechts
                if (turnradius < 0)
                    execute_Turn(45);
                else
                    execute_Turn(-45);
                break;

            default:
                finished();
                break;
        }
    }


    // void update_TurnLeft()
    // {
    //     switch (state)
    //     {
    //         case 1: // Achteruit
    //             execute_Backward();
    //             break;
    //         case 2: // draai links
    //             execute_TurnLeft(45);
    //             break;
    //         case 3: // vooruit tot x graden gedraaid AGV (controle IMU) & controle einde mat
    //             execute_MoveTillRotationReached(90);
    //             break;
    //         case 4: // draai rechts
    //             execute_TurnRight(45);
    //             break;

    //         default:
    //             finished();
    //             break;
    //     }
    // }

    // void update_TurnRight()
    // {
    //     switch (state)
    //     {
    //         case 1: // Achteruit
    //             execute_Backward();
    //             break;
    //         case 2: // draai rechts
    //             execute_TurnRight(45);
    //             break;
    //         case 3: // vooruit tot x graden gedraaid AGV (controle IMU) & controle einde mat
    //             execute_MoveTillRotationReached(90);
    //             break;
    //         case 4: // draai links
    //             execute_TurnLeft(45);
    //             break;

    //         default:
    //             finished();
    //             break;
    //     }
    // }






// --------------------------  PUBLIC -------------------------------

public:
    Command() {}

    Command(AutomatedGuidedVehicle *obj)
    {
        vehicle = obj;
    }

    void Update()
    {
        if (state == 0)
            return;

        if (command == "MOVE FORWARD")
        {
            update_Forward();
            return;
        }
        if (command == "MOVE BACKWARD")
        {
            update_Backward();
            return;
        }        
        if (command == "DODGE")
        {
            update_Dodge();
            return;
        }
        if (command == "TURN")
        {
            update_Turn();
            return;
        }

        // if (command == "TURN LEFT")
        // {
        //     update_TurnLeft();
        //     return;
        // }
        // if (command == "TURN RIGHT")
        // {
        //     update_TurnRight();
        //     return;
        // }        
        // if (command == "TURN ARROUND")
        // {
        //     update_TurnArround();
        //     return;
        // }
        if (command == "MOVE TO AREA")
        {
            update_MoveToArea();
            return;
        }
    }

    bool IsFinished()
    {
        return (state == 0);
    }

    void MoveForward()
    {
        execute("MOVE FORWARD");
    }
    void MoveBackward()
    {
        execute("MOVE BACKWARD");
    }    
    void Dodge()
    {
        execute("DODGE");
    }
    void Turn(int value)
    {
        turnradius = value;
        execute("TURN");
    }

    // void TurnLeft()
    // {
    //     execute("TURN LEFT");
    // }
    // void TurnRight()
    // {
    //     execute("TURN RIGHT");
    // }
    // void TurnArround()
    // {
    //     execute("TURN ARROUND");
    // }

    void MoveToArea()
    {
        execute("MOVE TO AREA");
    }


    void Stop()
    {
        state = 0;
        vehicle->Stop();
        command = "";
        busy = false;
    }
};

#endif // Commands
