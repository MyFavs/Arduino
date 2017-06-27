// #ifndef Command_Rotate_h   // If Class is not defined, then define it and use underlying code (Double Usage)
// #define Command_Rotate_h

// #include "AutomatedGuidedVehicle.h"

// class Command_Rotate
// {
//     int state = 0;
//     int _direction = 0;
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



// public:

//     Command_Rotate() {}

//     Command_Rotate(AutomatedGuidedVehicle *obj)
//     {   
//         vehicle = obj;
//     }
//     void Update()
//     {
//       if (state == 0)
//         return;
      
//       switch(state)
//       {
//           case 1:     // Achteruit 
//               execute_Backward();
//               break;
//           case 2:     // draai links/rechts 90 graden
//               execute_Turn(45, _direction);
//               break;
//           case 3:     // vooruit tot x graden gedraaid AGV (controle IMU) & controle einde mat
//               execute_MoveTillRotationReached(90);
//               break;
//           case 4:     // draai links/rechts 90 graden terug
//               _direction = -_direction;
//               execute_Turn(45, _direction);
//               break;
              
//           default:
//             Serial.println("# Finished Command: ROTATE");
//             Serial.println("------------------------------");
//             state = 0;
//             break;
              
//       }
//     }

//     void Left()
//     {
//         Serial.println("# Executing Command: ROTATE LEFT");

//         if (vehicle->IsMoving())
//         {
//             Serial.println("RotateLeft Rejected!!!");
//             return;
//         }
//         _direction = -1;
//         state = 1;
//     }

//     void Right()
//     {
      
//         Serial.println("# Executing Command: ROTATE RIGHT");

//         if (vehicle->IsMoving())
//         {
//             Serial.println("RotateRight Rejected!!!");
//             return;
//         }
//         _direction = 1;
//         state = 1;
//     }

//     bool IsFinished()
//     {
//         return (state == 0);
//     }

//     void Stop()
//     {
//         _direction = 0;
//         state = 0;
//         vehicle->Stop();
//     }
// };

// #endif //Command_Rotate_h
