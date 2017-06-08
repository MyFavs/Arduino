#include <AutomatedGuidedVehicle.h>

AutomatedGuidedVehicle vehicle;

int state = 0;
unsigned long _time = millis();

void setup()
{
    vehicle.SetTime(_time);
    vehicle.InitializeStepper(8, 9, 10, 11);
    vehicle.InitalizeMotor(6, 7);
    vehicle.Sensors.InitalizeUltrasoon(2, 4, 3, 5);
    vehicle.Sensors.InitalizeDetectors(40, 41);
//    vehicle.InitalizeButtons(42, 43, 44); // Left Turn Stepper, Right Turn Stepper, Start Process
}

void loop()
{
    switch (state)
    {
        case 0:
            if (vehicle.IsStartButtonPressed)
            {
                delay(1000);
                state = 1;
            }
            break;
        case 1:
            if (!vehicle.IsMovingToMat())
            {
                vehicle.MoveToMat();
            }
            else if (vehicle.HasMovedOnMat())
            {
                state = 2;
            }
            break;
        case 2:
            if (vehicle.HasMovedToMat())
            {
                
            }
            break;
    }

    vehicle.Update();
}

void moveToMat()
{
    // 1) rijd naar mat toe
    // 2) stop als je op de mat bent (controle IMU)
}

void rotateLeft()
{
    // 1) Achteruit 
    // 2) draai links 90 graden
    // 3) vooruit tot 90 graden gedraaid AGV (controle IMU) & controle einde mat
}

void rotateRight()
{
    // 1) Achteruit 
    // 2) draai rechts 90 graden
    // 3) vooruit tot 90 graden gedraaid AGV (controle IMU) & controle einde mat
}

void dodge()
{
    // 1) Achteruit
    // 2) draai 45 graden naar links
    // 3) vooruit x meter (IMU)
    // 4) draai 45 graden naar rechts
    // 5) vooruit x meter (IMU)
    // 6) draai 45 graden naar rechts
    // 7) vooruit x meter (IMU)
    // 8) draai 45 graden naar links
    // 9) vooruit x meter (IMU)
}

void moveForward()
{
    // totdat er een ding is of het einde van de mat
}