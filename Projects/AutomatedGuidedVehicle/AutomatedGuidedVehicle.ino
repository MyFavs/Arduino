#include "AutomatedGuidedVehicle.h"
#include "Commands.h"
#include "Sensors.h"
#include <IRremote.h>
#include "RemoteControls.h"
#include <Wire.h>

AutomatedGuidedVehicle vehicle;
Command cmd(&vehicle);
RemoteControls remoteControl;




// -- Infra Red
IRrecv infraRedReveiver(12);
decode_results infraRedResult;



int state = 0;
bool _processing = false;
bool _showSensorLog = false;
bool busy = false;

int harvestdirection = -180;

int moveState = 0;
int moveDirection = 0;


void setup()
{
    Serial.begin(9600);
    Serial.println("Initializing");
    IMU_Initialize();
    infraRedReveiver.enableIRIn(); // Start the receiver
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

    //remoteControl.UseTypeCarMp3();
    remoteControl.UseTypeHumax();
}

void loop()
{
   
    vehicle.Time = millis();
    vehicle.Sensors.Time = vehicle.Time;

    SetCommandFromRemote();


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


void printState(String value)
{
    Serial.print(">HARVESTING STEP ");
    Serial.print(state);
    Serial.print(":");
    Serial.println(value);
}

bool IsFinished()
{
    return (state == 0);
}

void finished()
{
    Serial.print("# Finished Hasvesting");
    Serial.println("-----------------------------------");
    state = 0;
    busy = false;
}


void Start()
{
    Serial.println("# Executing Start Harvesting");
    if (state != 0 || busy)
    {
        Serial.println("Harvesting Rejected!!!");
        return;
    }
    state = 1;
}

// ------------------------ EXECTUTE COMMANDS --------------------
void execute_MoveTillAreaDetected()
{
    if (cmd.IsFinished() && !busy)
    {
        printState("MOVE TO AREA");
        cmd.MoveToArea();
        busy = true;
    }
    if (cmd.IsFinished())
    {
        state++;
        busy = false;
    }          
}  

void execute_Boost()
{
    if (cmd.IsFinished() && !busy)
    {
        printState("BOOST");
        cmd.Boost();
        busy = true;
    }
    if (cmd.IsFinished())
    {
        state++;
        busy = false;
    }          
} 

void execute_MoveTillObjectDetected(int rotate, int dodge)
{
    if (cmd.IsFinished() && !busy)
    {
        printState("MOVE");
        cmd.MoveForward();
        busy = true;
    }
    if (cmd.IsFinished())
    {
        if (vehicle.Sensors.IsGroundDetected())
        {
            state = rotate; // Naar roteren 180 graden
        }
        if (vehicle.Sensors.IsObjectDetected())
        {
            state = dodge; // Dodge
        }
        busy = false;
    }    
}

void execute_Dodge(int next)
{
    if (cmd.IsFinished() && !busy)
    {
        printState("DODGE");
        cmd.Dodge();
        busy = true;
    }
    if (cmd.IsFinished())
    {
        if (vehicle.Sensors.IsGroundDetected())
        {
            state = 999;
        }        
        else
        {
            state = next;
        }
        busy = false;
    }    
}

void execute_TurnAround(int next)
{
    if (cmd.IsFinished() && !busy)
    {
        printState("TURN AROUND");
        cmd.Turn(harvestdirection);  // of -180
        busy = true;
    }
    if (cmd.IsFinished())
    {
        if (vehicle.Sensors.IsGroundDetected())
        {
            state = 999;
        }        
        else
        {
            state = next;
        }
        harvestdirection = -harvestdirection;
        busy = false;
    }    
}


// ---------------------------- UPDATE -------------------
void Update()
{
    if (state == 0)
        return;

    switch (state)
    {
        case 1:
            if (!vehicle.Sensors.IsGroundDetected())
            {
                state = 3;
                break;
            }
            execute_MoveTillAreaDetected();
            break;
        case 2: 
            execute_Boost();
            break;
        case 3: 
            execute_MoveTillObjectDetected(5, 6);
            break;

        case 5: 
            execute_TurnAround(3);
            break;

        case 6: 
            execute_Dodge(3);
            break;

        default:
            finished();
            break;
    }
}




void SetCommandFromRemote()
{
    if (infraRedReveiver.decode(&infraRedResult))
    {
        remoteControl.SetCode(infraRedResult.value);
        infraRedReveiver.resume(); // Receive the next value
    }

    if (remoteControl.HasCode())
    {
        if (remoteControl.IsCommand("OK","POWER"))
        {
            cmd.Stop();
        }
        else if (remoteControl.IsCommand("INFO"))
        {
            _showSensorLog = !_showSensorLog;
            Serial.print("# Sensor Log ");
            Serial.println(_showSensorLog);
        }
        else if (remoteControl.IsCommand("CH+"))
        {
            vehicle.Step(1, 4);
        }
        else if (remoteControl.IsCommand("CH-"))
        {
            vehicle.Step(-1, 4);
        }
        else if (remoteControl.IsCommand("VOL+"))
        {
            vehicle.Sensors.SetDuckySensor(true);
        }
        else if (remoteControl.IsCommand("VOL-"))
        {
            vehicle.Sensors.SetDuckySensor(false);
        }

        

        if (!isExecutingCommand())
        {
            if (remoteControl.IsCommand("1"))
            {
                cmd.MoveToArea();
            }
            else if (remoteControl.IsCommand("2"))
            {
                cmd.Boost();
            }
            else if (remoteControl.IsCommand("LEFT"))
            {
                cmd.Turn(-90);
            }
            else if (remoteControl.IsCommand("RIGHT"))
            {
                cmd.Turn(90);
            }
            else if (remoteControl.IsCommand("UP"))
            {
                cmd.MoveForward();
            }
            else if (remoteControl.IsCommand("DOWN"))
            {
                cmd.MoveBackward();
            }

            else if (remoteControl.IsCommand("BLUE"))
            {
                cmd.Turn(180);
            }
            else if (remoteControl.IsCommand("YELLOW"))
            {
                cmd.Turn(-180);
            }
            else if (remoteControl.IsCommand("RED"))
            {
                cmd.Dodge();
            }



            else if (remoteControl.IsCommand("GUIDE"))
            {
                Start(); // StartHarvesting
            }
            remoteControl.Reset();
        }
    }
}

// --------------------------- IMU Stuff --------------------------

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
            return;
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
