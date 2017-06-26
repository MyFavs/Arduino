#ifndef Command_MoveToMat_h   // If Class is not defined, then define it and use underlying code (Double Usage)
#define Command_MoveToMat_h

#include "AutomatedGuidedVehicle.h"

class Command_MoveToMat
{
    bool busy = false;
    int state = 0;
    AutomatedGuidedVehicle *vehicle;


    void printState(String value)
    {
      Serial.print(">STEP ");
      Serial.print(state);
      Serial.print(":");
      Serial.println(value);
    }


    void execute_MoveTillGroundDetected()
    {
        if (!vehicle->IsMoving() && !busy)
        {
            printState("MOVE FORWARD");
            vehicle->Forward(0, 3);
            vehicle->IMU.ResetZ();
            busy = true;
        }
       if (!vehicle->Sensors.IsGroundDetected())
       {
           printState("GROUND NOT DETECTED");
           vehicle->Stop();
           state++;
           busy = false;
       }          
    }


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
      
      switch(state)
      {
          case 1:     // Voorruit totdat grond gedetecteerd is 
              execute_MoveTillGroundDetected();
              break;
              
          default:
            Serial.println("# Finished Command: MOVE FORWARD");
            Serial.println("-----------------------------------");
            state = 0;
            break;
              
      }
    }


        bool IsFinished()
        {
            return (state == 0);
        }
        
        void Start()
        {
            Serial.println("# Executing Command: MOVE FORWARD");
            if (vehicle->IsMoving() || busy)
                {
                    Serial.println("MoveForward Rejected!!!");
                    return;
                }
            if (IsFinished()) 
                state = 1;
        }
        
        void Stop()
        {
            state = 0;
            vehicle->Stop();
        }



};

#endif // Command_MoveToMat_h
