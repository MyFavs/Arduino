// ----------------------------------------
// Ultrasoon Library v1.0
// ----------------------------------------
// By Tom
//
// Last Modification Date:  30-5-2017
// ----------------------------------------

#ifndef Ultrasoon_h   // If Class is not defined, then define it and use underlying code (Double Usage)
#define Ultrasoon_h

class Ultrasoon
{
	const int temp = 30;
	
	float duration;
	int distance;
	float c = (331 + (0.6 * temp))*100/1000000;
	
	int trigPin;
	int echoPin;
	
	public:
	
	Ultrasoon() {}
	
	Ultrasoon (int tPin, int ePin)
	{
		Initalize(tPin, ePin);
	}

	// -- Commands --

	void Initalize (int tPin, int ePin)
	{
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
		
		duration = pulseIn(echoPin, HIGH);
		distance = (duration/2) * c * 10;
		return distance;
	}
};

#endif   // Ultrasoon_h