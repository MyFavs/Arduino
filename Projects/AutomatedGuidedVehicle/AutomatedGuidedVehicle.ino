#include "AutomatedGuidedVehicle.h"
#include "Command_Dodge.h"
#include "Command_Move.h"
#include "Command_MoveForward.h"
#include "Command_MoveToMat.h"
#include "Command_Rotate.h"
#include "Sensors.h"
#include <IRremote.h>
#include <Wire.h>

AutomatedGuidedVehicle vehicle;

Command_Dodge cmd_Dodge(&vehicle);
Command_MoveToMat cmd_MoveToMat(&vehicle);
Command_Rotate cmd_Rotate(&vehicle);
Command_MoveForward cmd_MoveForward(&vehicle);
Command_Move cmd_Move(&vehicle);

IRrecv irrecv(12);

decode_results results;

int state = 0;
bool _processing = false;

int moveState = 0;
int moveDirection = 0;

String Command = "";
long Code = 0;

void CarMP3_Remote();

void setup()
{
  IMU_Initialize();
  irrecv.enableIRIn(); // Start the receiver
  vehicle.InitializeStepper(8, 9, 10, 11);
  vehicle.InitializeMotor(6, 7);
  vehicle.Sensors.InitializeUltrasonicPins(2, 4, 3, 5);
  vehicle.Sensors.InitializeDetectorPins(40, 41);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  Serial.println("IM OKAY Setup");
//  Code = 1;
//  Command = "1";
}

void loop()
{
  //Serial.println("IM OKAY Loop");
  vehicle.Time = millis();
  vehicle.Sensors.Time = vehicle.Time;
  Serial.println(vehicle.Time);
  // --------------AFSTANDSBEDIENING UITVRAGEN---------------

  if (Command == "4" && Code > 0)
  {
    vehicle.Stop();
    cmd_MoveForward.Stop();
    cmd_Rotate.Stop();
    cmd_Dodge.Stop();
  }

  if (!isExecutingCommand())
  {
    if (Code > 0)
    {
      Serial.println(Code);
      if (Command == "1")
      {
        cmd_MoveForward.Start();
        //vehicle.Forward(1000);
        //vehicle.TurnLeft(90);
      }
      else if (Command == "2")
      {
        cmd_Rotate.Left();
      }
      else if (Command == "3")
      {
        cmd_Dodge.Start();
      }
    }
    Code = 0;
    Command = "";
  }

  if (irrecv.decode(&results))
  {
    //Serial.println(results.value);
    Code = results.value;
    CarMP3_Remote();
    irrecv.resume(); // Receive the next value
  }

  if (Command != "")
  {
    Serial.println(Command);
  }
  processUpdate();
  IMU_Update();
  vehicle.Sensors.Update();
  MoveUpdate();
  cmd_Dodge.Update();
  cmd_MoveForward.Update();
  cmd_Rotate.Update();
  vehicle.Update();
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
    if (MoveIsFinished())
    {
      MoveStart();
    }

    if (MoveIsFinished())
    {
      state = 0;
      _processing = false;
    }
    break;
  }
}

void MoveStart()
{
  moveState = 1;
  moveDirection = -1;
}

bool MoveIsFinished()
{
  return (moveState == 0);
}

void MoveUpdate()
{
  switch (moveState)
  {
  case 1:
    if (cmd_MoveForward.IsFinished())
    {
      cmd_MoveForward.Start();
    }

    if (cmd_MoveForward.IsFinished())
    {
      if (vehicle.Sensors.IsObjectDetected())
      {
        moveState = 2;
      }

      if (vehicle.Sensors.IsGroundDetected())
      {
        moveState = 3;
      }
    }

    break;
  case 2:
    if (cmd_Dodge.IsFinished())
    {
      cmd_Dodge.Start();
    }

    if (cmd_Dodge.IsFinished())
    {
      moveState = 1;
    }
    break;

  case 3:
    if (cmd_Rotate.IsFinished())
    {
      if (moveDirection == -1)
      {
        cmd_Rotate.Left();
      }
      else if (moveDirection == 1)
      {
        cmd_Rotate.Right();
      }
    }

    if (cmd_Rotate.IsFinished())
    {
      moveState = 4;
    }
    break;
  case 4:
    if (cmd_Rotate.IsFinished())
    {
      if (moveDirection == -1)
      {
        cmd_Rotate.Left();
      }
      else if (moveDirection == 1)
      {
        cmd_Rotate.Right();
      }
    }

    if (cmd_Rotate.IsFinished())
    {
      moveState = 1;
      moveDirection = -moveDirection;
    }
    break;
  }
}

void CarMP3_Remote()
{
  switch (Code)
  {
  case 16753245:
    Command = "CH-";
    break;
  case 16736925:
    Command = "CH";
    break;
  case 16769565:
    Command = "CH+";
    break;
  case 16720605:
    Command = "PREV";
    break;
  case 16712445:
    Command = "NXT";
    break;
  case 16761405:
    Command = "PLAY";
    break;
  case 16769055:
    Command = "VOL-";
    break;
  case 16754775:
    Command = "VOL+";
    break;
  case 16748655:
    Command = "EQ";
    break;
  case 16738455:
    Command = "0";
    break;
  case 16724175:
    Command = "1";
    break;
  case 16718055:
    Command = "2";
    break;
  case 16743045:
    Command = "3";
    break;
  case 16716015:
    Command = "4";
    break;
  case 16726215:
    Command = "5";
    break;
  case 16734885:
    Command = "6";
    break;
  case 16728765:
    Command = "7";
    break;
  case 16730805:
    Command = "8";
    break;
  case 16732845:
    Command = "9";
    break;
  case 16750695:
    Command = "100+";
    break;
  case 16756815:
    Command = "200+";
    break;
  default:
    Command = "";
    break;
  }

  if (Command == "")
  {
    Code = 0;
    Command = "";
  }
}

void Reset()
{
  Code = 0;
  Command = "";
}

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
  if (vehicle.Time % 100 == 0)
  {
    IMU_recordAccelRegisters();
    IMU_recordGyroRegisters();
    if (vehicle.IMU.rotZ > 1 || vehicle.IMU.rotZ < -1)
    {
      vehicle.IMU.TotalRotationZ = vehicle.IMU.TotalRotationZ + vehicle.IMU.rotZ / 10;
    }
//    Serial.print("TotalRotationZ: ");
//    Serial.println(vehicle.IMU.TotalRotationZ);
  }
}
