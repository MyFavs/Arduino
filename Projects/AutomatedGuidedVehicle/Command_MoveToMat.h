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


    void execute_MoveTillGroundNotDetected()
    {
        if (!vehicle->IsMoving() && !busy)
        {
            printState("MOVE FORWARD");
            vehicle->Forward(0, 3);
            vehicle->IMU.ResetZ();
            busy = true;
        }
       if (vehicle->Sensors.IsGroundDetected())
       {
      
         printState("GROUND NOT DETECTED ANYMORE");
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
                  execute_MoveTillGroundNotDetected();
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
            Serial.println("# Executing Command: MOVE FORWARD (TO MAT)");
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




//
//
//        void Update()
//        {
//            if (state == 0)
//                return;
//
//            if (vehicle->Time % 100 != 0)
//                return;
//                
//            switch(state)
//            {
//                case 1:
//                    if (!vehicle->IsMoving() && !busy)
//                        vehicle->Forward(30000);
//                        busy = true;
//
//                    if (!vehicle->Sensors.IsGroundDetected())
//                        state++;
//                        vehicle->Stop();
//                        busy = false;
//                    break;
//                case 2:
//                   if (!vehicle->IsMoving() && !busy)
//                   {
//                       vehicle->Forward(1000);
//                       busy = true;
//                   }
//
//                   if (!vehicle->IsMoving())
//                   {
//                       state = 0;
//                       busy = false;
//                   }
//                    break;
//            }
//        }
//
//        bool IsFinished()
//        {
//            return (state == 0);
//        }
//
//        void Start()
//        {
//            Serial.println("- Executing Command: MOVE TO MAT");
//
//            if (IsFinished()) 
//                state = 1;
//        }
};

#endif // Command_MoveToMat_h
