#include "AutomatedGuidedVehicle.h"
#include "Commands.h"
// #include "Command_Move.h"
// #include "Command_MoveForward.h"
// #include "Command_MoveToMat.h"
// #include "Command_Rotate.h"
#include "Sensors.h"
#include <IRremote.h>
#include "RemoteControls.h"
#include <Wire.h>

AutomatedGuidedVehicle vehicle;

Command cmd(&vehicle);
// Command_MoveToMat cmd_MoveToMat(&vehicle);
// Command_Rotate cmd_Rotate(&vehicle);
// Command_MoveForward cmd_MoveForward(&vehicle);
// Command_Move cmd_Move(&vehicle);

RemoteControls _remotes;

IRrecv irrecv(12);

decode_results results;

int state = 0;
bool _processing = false;
bool _showSensorLog = false;
bool busy = false;

int moveState = 0;
int moveDirection = 0;

void setup()
{
    Serial.begin(9600);
    Serial.println("Initializing");
    IMU_Initialize();
    irrecv.enableIRIn(); // Start the receiver
    vehicle.InitializeStepper(8, 9, 10, 11);
    vehicle.InitializeMotor(6, 7);
    vehicle.Sensors.InitializeUltrasonicPins(2, 4, 3, 5); // Trig1, Echo1, Trig2, Echo2
    vehicle.Sensors.InitializeDetectorPins(40, 41);
    pinMode(13, OUTPUT);
    pinMode(22, OUTPUT);

    digitalWrite(13, HIGH); // Needed for IR Remote
    digitalWrite(22, HIGH); // Needed as Power for the MotorController

    Serial.println("");
    Serial.println("Waiting for command...");

    //_remotes.UseTypeCarMp3();
    _remotes.UseTypeHumax();
}

void loop()
{
   
    vehicle.Time = millis();
    vehicle.Sensors.Time = vehicle.Time;
    // --------------AFSTANDSBEDIENING UITVRAGEN---------------

    if (irrecv.decode(&results))
    {
        _remotes.SetCode(results.value);
        irrecv.resume(); // Receive the next value
    }

    if (_remotes.HasCode())
    {
        if (_remotes.IsCommand("4", "POWER"))
        {
            cmd.Stop();
        }
        if (_remotes.IsCommand("EQ", "INFO"))
        {
            _showSensorLog = !_showSensorLog;
            Serial.print("# Sensor Log ");
            Serial.println(_showSensorLog);
        }

        if (!isExecutingCommand())
        {
            if (_remotes.IsCommand("1"))
            {
                cmd.MoveToArea();
            }

            else if (_remotes.IsCommand("LEFT"))
            {
                cmd.Turn(-90);
            }
            else if (_remotes.IsCommand("RIGHT"))
            {
                cmd.Turn(90);
            }
            else if (_remotes.IsCommand("UP"))
            {
                cmd.MoveForward();
            }
            else if (_remotes.IsCommand("DOWN"))
            {
                cmd.MoveBackward();
            }
            else if (_remotes.IsCommand("BLUE"))
            {
                cmd.Turn(180);
            }
            else if (_remotes.IsCommand("YELLOW"))
            {
                cmd.Turn(-180);
            }
            else if (_remotes.IsCommand("RED"))
            {
                cmd.Dodge();
            }

            // else if (_remotes.IsCommand("CH+"))
            // {
            //     vehicle.Sensors.Enabled = false;
            //     vehicle.Step(100, 4);
            // }
            // else if (_remotes.IsCommand("CH-"))
            // {
            //     vehicle.Sensors.Enabled = false;
            //     vehicle.Step(100, -4);
            // }

            else if (_remotes.IsCommand("GUIDE"))
            {
                start(); // StartHarvesting
            }
            _remotes.Reset();
        }
    }

    //processUpdate();
    IMU_Update();
    vehicle.Sensors.Update();
    //MoveUpdate();
    cmd.Update();
    vehicle.Update();
}

bool isExecutingCommand()
{
    if (vehicle.IsMoving())
    {
        return true;
    }

    if (!(cmd.IsFinished() || _processing))
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

// void processUpdate()
// {
//     switch (state)
//     {
//     case 0:
//         return;

//     case 1:
//         if (cmd_MoveToMat.IsFinished() && !busy)
//         {
//             //delay(1000);
//             cmd_MoveToMat.Start();
//             busy = true;
//             Serial.println("STATE 1");
//         }

//         if (cmd_MoveToMat.IsFinished())
//         {
//             state++;
//             busy = false;
//         }

//         break;

//     case 2:
//         if (cmd_Rotate.IsFinished() && !busy)
//         {
//             cmd_Rotate.Right();
//             busy = true;
//             Serial.println("STATE 2");
//         }

//         if (cmd_Rotate.IsFinished())
//         {
//             state++;
//             busy = false;
//         }
//         break;

//     case 3:
//         if (cmd_MoveForward.IsFinished() && !busy)
//         {
//             cmd_MoveForward.Start();
//             busy = true;
//             Serial.println("STATE 3");
//         }
//         if (cmd_MoveForward.IsFinished())
//         {
//             state++;
//             busy = false;
//         }
//         break;

//     case 4:
//         if (cmd_Rotate.IsFinished() && !busy)
//         {
//             cmd_Rotate.Left();
//             busy = true;
//             Serial.println("STATE 4");
//         }

//         if (cmd_Rotate.IsFinished())
//         {
//             state++;
//             busy = false;
//         }
//         break;

//     case 5:
//         if (MoveIsFinished() && !busy)
//         {
//             MoveStart();
//             busy = true;
//             Serial.println("STATE 5");
//         }

//         if (MoveIsFinished())
//         {
//             state = 0;
//             _processing = false;
//             busy = false;
//         }
//         break;
//     default:
//         break;
//     }
// }

// void MoveStart()
// {
//     moveState = 1;
//     moveDirection = -1;
// }

// bool MoveIsFinished()
// {
//     return (moveState == 0);
// }

// bool jo = false;

// void MoveUpdate()
// {
//     switch (moveState)
//     {
//     case 1:
//         if (cmd_MoveForward.IsFinished() && !jo)
//         {
//             cmd_MoveForward.Start();
//             jo = true;
//         }

//         if (cmd_MoveForward.IsFinished())
//         {
//             if (vehicle.Sensors.IsObjectDetected())
//             {
//                 moveState = 2;
//             }

//             if (vehicle.Sensors.IsGroundDetected())
//             {
//                 moveState = 3;
//             }
//             jo = false;
//         }

//         break;
//     case 2:
//         if (cmd_Dodge.IsFinished() && !jo)
//         {
//             cmd_Dodge.Start();
//             jo = true;
//         }

//         if (cmd_Dodge.IsFinished())
//         {
//             moveState = 1;
//             jo = false;
//         }
//         break;

//     case 3:
//         if (cmd_Rotate.IsFinished() && !jo)
//         {
//             if (moveDirection == -1)
//             {
//                 cmd_Rotate.Left();
//             }
//             else if (moveDirection == 1)
//             {
//                 cmd_Rotate.Right();
//             }
//             jo = true;
//         }

//         if (cmd_Rotate.IsFinished())
//         {
//             moveState = 4;
//             jo = false;
//         }
//         break;
//     case 4:
//         if (cmd_Rotate.IsFinished() && !jo)
//         {
//             if (moveDirection == -1)
//             {
//                 cmd_Rotate.Left();
//             }
//             else if (moveDirection == 1)
//             {
//                 cmd_Rotate.Right();
//             }
//             jo = true;
//         }

//         if (cmd_Rotate.IsFinished())
//         {
//             moveState = 1;
//             moveDirection = -moveDirection;
//             jo = false;
//         }
//         break;
//     }
// }

void IMU_recordRegisters(byte command, long value[])
{
    Wire.beginTransmission(vehicle.IMU.address);
    byte error = Wire.endTransmission();
    if (error != 0)
    {
        Serial.print(millis());
        Serial.println("   Device Disabled");
        return;
    }

    IMU_sendCommand(command);
    Wire.requestFrom(vehicle.IMU.address, 6);
    while (Wire.available() < 6)
    {
        if (millis() > vehicle.Time + 500)
        {
            return;
        }
    }
    value[0] = Wire.read() << 8 | Wire.read();
    value[1] = Wire.read() << 8 | Wire.read();
    value[2] = Wire.read() << 8 | Wire.read();
}

void IMU_recordAccelRegisters()
{
    long array[3];
    IMU_recordRegisters(0x3B, array);
    vehicle.IMU.gForceX = array[0] / 16384.0;
    vehicle.IMU.gForceY = array[1] / 16384.0;
    vehicle.IMU.gForceZ = array[2] / 16384.0;
}

void IMU_recordGyroRegisters()
{
    long array[3];
    IMU_recordRegisters(0x43, array);
    vehicle.IMU.rotX = array[0] / 131.0;
    vehicle.IMU.rotY = array[1] / 131.0;
    vehicle.IMU.rotZ = array[2] / 131.0;
}

void IMU_sendCommand(uint8_t command)
{
    Wire.beginTransmission(vehicle.IMU.address);
    Wire.write(command);
    Wire.endTransmission();
}

void IMU_sendCommand(uint8_t command, byte value)
{
    Wire.beginTransmission(vehicle.IMU.address);
    Wire.write(command);
    Wire.write(value);
    Wire.endTransmission();
}

void IMU_Initialize()
{
    Wire.begin();
    IMU_sendCommand(0x6B, 0);
    IMU_sendCommand(0x1B, 0);
    IMU_sendCommand(0x1C, 0);
}

void IMU_Update()
{
    if (!vehicle.Sensors.Enabled)
        return;

    if (vehicle.Time % 100 == 0)
    {
        //IMU_recordAccelRegisters();
        IMU_recordGyroRegisters();
        if (vehicle.IMU.rotZ > 1 || vehicle.IMU.rotZ < -1)
        {
            vehicle.IMU.TotalRotationZ = vehicle.IMU.TotalRotationZ + vehicle.IMU.rotZ / 10;
        }

        if (_showSensorLog)
        {
            Serial.print("---- Rotation: ");
            Serial.print(vehicle.IMU.TotalRotationZ);
            //      Serial.print("     Gforce: ");
            //      Serial.print(vehicle.IMU.gForceZ);
            Serial.print("     ScanState: ");
            Serial.print(vehicle.Sensors.GetScanState());

            Serial.print("     Left: ");
            Serial.print(vehicle.Sensors.UltrasonicDistance1);
            Serial.print("     Right: ");
            Serial.print(vehicle.Sensors.UltrasonicDistance2);

            Serial.println("");
        }
    }
}
