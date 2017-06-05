// ----------------------------------------
// Stepper Library
// ----------------------------------------
// By ET14
//
// Last Modification Date:  15-5-2017
// ----------------------------------------


#ifndef Stepper_KE56KM2_h   // If Class is not defined (Double Usage)
#define Stepper_KE56KM2_h

// commando geven: rotate(+-Graden,+-Snelheid)

// timer op 0

// stappen = stapgrootte in map met graden

// void update, pause, continue, stop, reverse

#include "arduino.h"

class Stepper_KE56KM2
{
	int _stepsInMotor = 200;
	
    int _currentState = 0;
	int _lastState = 0;
    int _speed;
    int _step;
	int _maxStep;
    int _motorPin[4];
    //unsigned long _timer;
	int _rotation = 0;
	int _lastRotation = 0;
	bool _paused = false;
	bool _finished = false;

    void initializePin(int id, int pin)
    {
      _motorPin[id] = pin;
      pinMode(_motorPin[id], OUTPUT);
    }

    int setMotorState(int state)
    {
		//    A+  A-  B+  B-
		
		//
	    //  Red    A+    --:             :--   B+   Yellow
		//                 :             :
		//                 :      O      :
		//                 :             :
	    //  Blue   A-    --:             :--   B-   White
		//
		//                         
		//
		//        <-- ClockWise       CounterWise -->
		
		
		//  Excitation Sequence
		//  ----------------------
		//  STEP           1  2  3  4    
		//  Red    (A+)    +  +  -  -    
		//  Yellow (B+)    -  +  +  -
		//  Blue   (A-)    -  -  +  +
		//  White  (B-)    +  -  -  +
		//
		
		
      switch (state) 
	  {
        case 1:  // Step 1
          digitalWrite(_motorPin[0], LOW);   //  A-
          digitalWrite(_motorPin[1], HIGH);  //  A+
          digitalWrite(_motorPin[2], LOW);   //  B+
          digitalWrite(_motorPin[3], HIGH);  //  B-
          break;
        case 2:  // Step 2
          digitalWrite(_motorPin[0], LOW);   //  A-
          digitalWrite(_motorPin[1], HIGH);  //  A+
          digitalWrite(_motorPin[2], HIGH);  //  B+
          digitalWrite(_motorPin[3], LOW);   //  B-
          break;
        case 3:  // Step 3
          digitalWrite(_motorPin[0], HIGH);  //  A-
          digitalWrite(_motorPin[1], LOW);   //  A+
          digitalWrite(_motorPin[2], HIGH);  //  B+
          digitalWrite(_motorPin[3], LOW);   //  B-
          break;
		case 4:  // Step 4
          digitalWrite(_motorPin[0], HIGH);  //  A-
          digitalWrite(_motorPin[1], LOW);   //  A+
          digitalWrite(_motorPin[2], LOW);   //  B+
          digitalWrite(_motorPin[3], HIGH);  //  B-
          break;
		  
		default:  // Stop sending power to the motor
          digitalWrite(_motorPin[0], LOW);   //  A-
          digitalWrite(_motorPin[1], LOW);   //  A+
          digitalWrite(_motorPin[2], LOW);   //  B+
          digitalWrite(_motorPin[3], LOW);   //  B-
		  _rotation = 0;
          break;
      }
	  _currentState = state;
      delay(1);
    }

	void rotateMotor()
	{
		if (_finished || _paused || _rotation == 0) 
		{
			return;
		}
		
		if (_rotation > 0)   // Rotate Right
		{
			if (_step >= _maxStep)
			{
				Stop();
				return;
			}
			_step++;
			
			_currentState++;
			if (_currentState > 4)
			{
			  _currentState = 1;
			}
		}
		else             // Rotate Left
		{			
			if (_step <= 0)
			{
				Stop();
				return;
			}
			_step--;
			
			_currentState--;
			if (_currentState < 1)
			{
			  _currentState = 4;
			}
		}
		setMotorState(_currentState);
    }



  public:
    Stepper_KE56KM2() {}

    Stepper_KE56KM2(int pin1, int pin2, int pin3, int pin4)
    {
		initializePin(0, pin1);
		initializePin(1, pin2);
		initializePin(2, pin3);
		initializePin(3, pin4);
    }
	
    void Rotate(int degree, int spd)
    {
		_rotation = 1;
		
		if (degree == 0)
		{
			return;
		}
		
		if (degree < 0)
		{
			Reverse();
			degree = -degree;
		}
		
		int steps = map(degree, 0, 359, 0, _stepsInMotor);
		Step(steps, spd);
		
    }
	
    void Step(int steps, int spd)
    {
		if (_rotation == 0)
		{
			_rotation = 1;
		}
		
		if (steps == 0 || spd == 0)
		{
			return;
		}
		
		if (spd < 0)
		{
			Reverse();
			spd = -spd;
		}
		
		if (steps < 0)
		{
			Reverse();
			steps = -steps;
		}

		
		if (spd > 8)
		{
			spd = 8;
		}
		
		_maxStep = steps;
		_speed = map(spd, 1, 8, 64, 8);
		
		if (_rotation > 0)
		{
			_step = 0;
		}
		else
		{
			_step = _maxStep;
		}
		
		_currentState = _lastState;  // return the last state when the motor has stopped.
		_finished = false;
    }
	

	void Pause()
	{
		if (_paused)
		{
		   return;
		}
		_paused = true;
		_lastState = _currentState;
		_lastRotation = _rotation;
		setMotorState(0);
	}
	
	void Stop()
	{
		_finished = true;
		_lastState = _currentState;
		_lastRotation = _rotation;
		setMotorState(0);
	}
	
	
	void Continue()
	{
		if (_finished)
		{
			return;
		}
		
		_paused = false;
		
		setMotorState(_lastState);
		_lastState = 0;
		_rotation = _lastRotation;
		
	}
	
	void Reverse()
	{
		_rotation = -_rotation;
	}
	
	
    void Update()
    {
		if (_finished || _paused) 
		{
			return;
		}

		//unsigned long _timer = millis();

		//if (_timer % _speed == 0) // Speed how fast the motor is running
		//{
		//	rotateMotor();
		//}

		if (millis() % _speed == 0) // Speed how fast the motor is running
		{
			rotateMotor();
		}
		
    }
	
	int IsRotating()
	{
		return _rotation;
	}
	
	bool IsFinished()
	{
		return _finished;
	}
	
	bool IsPaused()
	{
		return _paused;
	}
	
	int CurrentStep()
	{
		return _step;
	}
	
	int CurrentDegree()
	{
		return map(CurrentStep(), 0, _stepsInMotor, 0, 359);
	}

};

#endif
