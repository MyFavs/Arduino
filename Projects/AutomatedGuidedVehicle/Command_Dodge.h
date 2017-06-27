// #ifndef Command_Dodge_h   // If Class is not defined, then define it and use underlying code (Double Usage)
// #define Command_Dodge_h

// #include "AutomatedGuidedVehicle.h"

// class Command_Dodge
// {
//     int state = 0;

//     AutomatedGuidedVehicle *vehicle;
//     bool busy = false;


//     void printState(String value)
//     {
//       Serial.print(">STEP ");
//       Serial.print(state);
//       Serial.print(":");
//       Serial.println(value);
//     }

//     void execute_Backward()
//     {
//         if (!vehicle->IsMoving() && !busy)
//         {
//             printState("BACKING UP");
//             vehicle->Backward(1000);
//             busy = true;
//         }

//         if (!vehicle->IsMoving())
//         {
//             state++;
//             busy = false;
//         }
//     }
//     void execute_TurnLeft(int value)
//     {
//       execute_Turn(value, -1);
//     }

//     void execute_TurnRight(int value)
//     {
//       execute_Turn(value, 1);
//     }

    
//     void execute_Turn(int value, int dir)
//     {
//         if (!vehicle->IsTurning() && !busy)
//         {
//             switch(dir)
//             {
//                 case -1:
//                     printState("STEER LEFT");
//                     vehicle->TurnLeft(value);
//                     break;
//                 case 1:
//                     printState("STEER RIGHT");
//                     vehicle->TurnRight(value);
//                     break;
//             }
//             busy = true;
//         }

//         if (!vehicle->IsTurning())
//         {
//             state++;
//             busy = false;
//         }
//     }

//     void execute_MoveTillRotationReached(int value)
//     {
//         if (!vehicle->IsMoving() && !busy)
//         {
//             printState("MOVE FORWARD");
//             vehicle->Forward(0, 3);
//             vehicle->IMU.ResetZ();
//             busy = true;
//         }
//        if (vehicle->IMU.TotalRotationZ >= value || vehicle->IMU.TotalRotationZ <= -value)
//        {
//            printState("ROTATION REACHED");
//            vehicle->IMU.ResetZ();
//            vehicle->Stop();
//            state++;
//            busy = false;
//        }          
//     }


//     public:

//     Command_Dodge() {}

//     Command_Dodge(AutomatedGuidedVehicle *obj)
//     {
//         vehicle = obj;
//     }

//     void Update()
//     {
//       if (state == 0)
//          return;

//       switch(state)
//       {
//           //  Achteruit
//           case 1:
//               execute_Backward();
//               break;
//           case 2:     // draai links 90 graden
//               execute_TurnLeft(45);
//               break;
//           case 3:     // vooruit tot x graden gedraaid AGV (controle IMU) & controle einde mat
//               execute_MoveTillRotationReached(45);
//               break;
//           case 4:     // draai rechts 90 graden
//               execute_TurnRight(90);
//               break;
//           case 5:     // vooruit tot x graden gedraaid AGV (controle IMU) & controle einde mat
//               execute_MoveTillRotationReached(90);
//               break;
//           case 6:     // draai links 90 graden
//               execute_TurnLeft(90);
//               break;
//           case 7:     // vooruit tot x graden gedraaid AGV (controle IMU) & controle einde mat
//               execute_MoveTillRotationReached(45);
//               break;
//           case 8:     // draai rechts 45 graden
//               execute_TurnRight(45);
//               break;
//           default:
//               Serial.println("# Finished Command: DODGE");
//               Serial.println("------------------------------");
//               state=0;
//               break;
//         }
//     }

//     bool IsFinished()
//     {
//         return (state == 0);
//     }

//     void Start()
//     {
//         Serial.println("# Executing Command: DODGE");
//         if (vehicle->IsMoving() || busy)
//             {
//                 Serial.println("Dodge Rejected!!!");
//                 return;
//             }
//         if (IsFinished()) 
//             state = 1;
//     }

//     void Stop()
//         {
//             state = 0;
//             vehicle->Stop();
//         }
// };

// #endif // Command_Dodge_h



