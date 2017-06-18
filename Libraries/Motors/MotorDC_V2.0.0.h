// ----------------------------------------
// DC motor Library v1.0
// ----------------------------------------
// By Erwin & Tom
//
// Last Modification Date:  06-06-2017
// ----------------------------------------

#ifndef MotorDC_h   // If Class is not defined, then define it and use underlying code (Double Usage)
#define MotorDC_h

class MotorDC
{
	int _motorPin[2];
	
	int _speed = 0;
	int _direction = 0;

	unsigned long _time;
	unsigned long _rotationTime;
	
	void initializePin(int id, int pin)
    {
      _motorPin[id] = pin;
      pinMode(_motorPin[id], OUTPUT);
    }
	
	int setMotorState()
    {
		Serial.print("Motor.setMotorState Speed=");
		int speed = map(_speed, 0, 8, 0, 255);
		Serial.println(speed);
		Serial.print("Direction: ");
		Serial.println(_direction);
		switch(_direction)
		{
			case 0:									// Stop
				analogWrite(_motorPin[0], 0);
				analogWrite(_motorPin[1], 0);
				break;
			case 1:									// RPWM move
				analogWrite(_motorPin[0], speed);
				analogWrite(_motorPin[1], 0);
				break;
			case -1:									// LPWM move
				analogWrite(_motorPin[0], 0);
				analogWrite(_motorPin[1], speed);
				break;
		}
	}
	
	
	public:
	
	// --Constructor--
	
	MotorDC() {}

    MotorDC(int RPWM, int LPWM)
    {
		Initialize(RPWM, LPWM);
    }
	
	// --Commands--

	void Initialize(int RPWM, int LPWM)
    {
		initializePin(0, RPWM);
		initializePin(1, LPWM);
    }
	
	void Rotate (int speed)
	{
		Rotate(speed, 0);
	}

	void Rotate(int speed, int rotationTime)
	{
		Serial.print("Motor.Rotate: ");
		Serial.print(speed);
		Serial.print(",");
		Serial.println(rotationTime);

		_time = millis();
		_rotationTime = rotationTime;
		_speed = speed;
		if (_speed == 0)
		{
			Stop();
			return;
		}
		
		if (_speed > 0)
		{
			_direction = 1;
		}
		else
		{
			_direction = -1;
			_speed = -_speed;
		}
		setMotorState();
	}
	
	void Reverse()
	{
		_direction = -_direction;
		setMotorState();
	}
	
	void Stop()
	{
		Serial.println("Motor.Stopped");	
		
		_direction = 0;
		_rotationTime = 0;
		setMotorState();
	}

	bool IsMoving()
	{
		return (_direction != 0);
	}

	void Update()
	{
		// Serial.print("Motor._rotationTime:");
		// Serial.print(_rotationTime);
		// Serial.print("  _time:");
		// Serial.println(millis());
		if (_rotationTime > 0)
		{
			if (millis() > _time + _rotationTime)
			{
				Stop();
			}
		}
	}

    void SetTime(unsigned long updateTime)
    {
        _time = updateTime;
    }
};

#endif   // MotorDC_h