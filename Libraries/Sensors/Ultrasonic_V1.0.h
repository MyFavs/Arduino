// ----------------------------------------
// Ultrasonic Library
// ----------------------------------------
// By Tom
//
// Last Modification Date:  26-6-2017
// ----------------------------------------

#ifndef Ultrasonic_h   // If Class is not defined, then define it and use underlying code (Double Usage)
#define Ultrasonic_h

class Ultrasonic
{
	String _version = "v1.0.3";

	int temp = 30;
	
	float duration;
	int distance;
	float c = (331 + (0.6 * temp)) * 100 / 1000000;
	
	int trigPin = 10;
	int echoPin = 11;
	
	
	public:
	
	Ultrasonic() {}
	
	Ultrasonic(int tPin, int ePin)
	{
		Initialize(tPin, ePin);
	}

	// -- Commands --

	void Initialize(int tPin, int ePin)
	{
		Serial.print("  [Ultrasonic] Initialized! ");
		Serial.println(_version);
		pinMode(trigPin, OUTPUT);
		pinMode(echoPin, INPUT);
		trigPin = tPin;
		echoPin = ePin;
	}
	
	int Scan()
	{
		digitalWrite(trigPin, LOW);
		delayMicroseconds(2);
		digitalWrite(trigPin, HIGH);
		delayMicroseconds(10);
		digitalWrite(trigPin, LOW);
		
		duration = pulseIn(echoPin, HIGH, 100);

		if (duration == 0)
		{
			return 0;
		}
		distance = (duration/2) * c * 10;
		return distance;
	}


};

#endif   // Ultrasonic_h