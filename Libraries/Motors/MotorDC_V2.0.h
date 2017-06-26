// ----------------------------------------
// DC motor Library
// ----------------------------------------
// By Erwin & Tom
//
// Last Modification Date:  26-6-2017
// ----------------------------------------

#ifndef MotorDC_h   // If Class is not defined, then define it and use underlying code (Double Usage)
#define MotorDC_h

class MotorDC
{
	String _version = "v2.0.3";
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
		int speed = map(_speed, 0, 8, 0, 255);

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
		Serial.print("  [MotorDC] Initialized! ");
		Serial.println(_version);
		initializePin(0, RPWM);
		initializePin(1, LPWM);
    }
	
	void Rotate(int speed)
	{
		Rotate(speed, 0);
	}

	void Rotate(int speed, int rotationTime)
	{
		Serial.print("  [MotorDC] Rotate Speed=");
		Serial.print(speed);
		if (rotationTime == 0)
		{
		  	Serial.println("  Duration is ENDLESS");
		}
		else
		{
			Serial.print("  Duration=");
			Serial.print(rotationTime);
  			Serial.println("ms");
		}
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
		Serial.print("  [MotorDC] Reverse, Direction is now ");
		Serial.println(_direction);
		setMotorState();
	}
	
	void Stop()
	{
		Serial.println("  [MotorDC] Stop");	
		
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