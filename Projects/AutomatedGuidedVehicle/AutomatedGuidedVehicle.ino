#include "AutomatedGuidedVehicle.h"
#include "Command_Dodge.h"
#include "Command_Move.h"
#include "Command_MoveForward.h"
#include "Command_MoveToMat.h"
#include "Command_Rotate.h"
#include "Sensors.h"
#include <IRremote.h>

AutomatedGuidedVehicle vehicle;

Command_Dodge cmd_Dodge(vehicle);
Command_MoveToMat cmd_MoveToMat(vehicle);
Command_Rotate cmd_Rotate(vehicle);
Command_MoveForward cmd_MoveForward;
Command_Move cmd_Move(vehicle);

IRrecv irrecv(12);

decode_results results;

unsigned long _time = millis();
int state = 0;
bool _processing = false;

int moveState = 0;
int moveDirection = 0;

String Command = "";
long Code = 0;

void CarMP3_Remote();


void setup()
{
  cmd_MoveForward.Initialize(&vehicle);
  irrecv.enableIRIn(); // Start the receiver
  vehicle.InitializeStepper(8, 9, 10, 11);
  vehicle.InitializeMotor(6, 7);
  vehicle.Sensors.InitializeUltrasonicPins(2, 4, 3, 5);
  vehicle.Sensors.InitializeDetectorPins(40, 41);
  vehicle.Sensors.InitializeRemoteControlPin(12);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  Code = 16753245;
  Command = "CH-";
}

void loop()
{
    
  // --------------AFSTANDSBEDIENING UITVRAGEN---------------
  if (!isExecutingCommand())
  {
    if (Code > 0)
    {
      Serial.println(Code);
      if (Command == "CH-")
      {
        vehicle.Name = "Tom";
        cmd_MoveForward.Start();
        //vehicle.Forward(1000);
        //vehicle.TurnLeft(90);
      }
      else
      {
        vehicle.Stop();
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

  if (Command != ""){Serial.println(Command);}
  processUpdate();
  vehicle.Update();
  MoveUpdate();
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
