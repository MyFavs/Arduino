class Command_Dodge
{
    int state = 0;
    AutomatedGuidedVehicle _vehicle;

    public:

    void Command_Dodge(AutomatedGuidedVehicle vehicle)
    {
        _vehicle = vehicle;
    }

    void Update()
    {

            
        switch(state)
        {
            // 1) Achteruit
            case 1:
                if (!vehicle.IsMoving())
                {
                    vehicle.Backward(1000);
                }

                if (!vehicle.IsMoving())
                {
                    step = 2;
                }
                break;
            // 2) draai 45 graden naar links
            case 2:
                if (!vehicle.IsTurning())
                {
                    vehicle.TurnLeft(45);
                }

                if (!vehicle.IsTurning())
                {
                    step = 3;
                }
                break;
            // 3) vooruit x meter (IMU)
            case 3:
                vehicle.Forward(1000);
                break;
            // 4) draai 45 graden naar rechts
            // 5) vooruit x meter (IMU)
            // 6) draai 45 graden naar rechts
            // 7) vooruit x meter (IMU)
            // 8) draai 45 graden naar links
            // 9) vooruit x meter (IMU)

        }
    }

    bool IsFinished()
    {
        return (state == 6);
    }
};



