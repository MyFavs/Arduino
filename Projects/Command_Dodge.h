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
                    state++;
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
                    state++;
                }
                break;
            // 3) vooruit x meter (IMU)
            case 3:
                if (!vehicle.IsMoving())
                {
                    vehicle.Forward(1000);
                }

                if (!vehicle.IsMoving())
                {
                    state++;
                }
                break;
            // 4) draai 45 graden naar rechts
            case 4:
                if (!vehicle.IsTurning())
                {
                    vehicle.TurnRight(45);
                }

                if (!vehicle.IsTurning())
                {
                    state++;
                }
                break;
            // 5) vooruit x meter (IMU)
            case 5:
                if (!vehicle.IsMoving())
                {
                    vehicle.Forward(1000);
                }

                if (!vehicle.IsMoving())
                {
                    state++;
                }
                break;
            // 6) draai 45 graden naar rechts
            case 6:
                if (!vehicle.IsTurning())
                {
                    vehicle.TurnRight(45);
                }

                if (!vehicle.IsTurning())
                {
                    state++;
                }
                break;
            // 7) vooruit x meter (IMU)
            case 7:
                if (!vehicle.IsMoving())
                {
                    vehicle.Forward(1000);
                }

                if (!vehicle.IsMoving())
                {
                    state++;
                }
                break;
            // 8) draai 45 graden naar links
            case 8:
                if (!vehicle.IsTurning())
                {
                    vehicle.TurnLeft(45);
                }

                if (!vehicle.IsTurning())
                {
                    state++;
                }
                break;
            // 9) vooruit x meter (IMU)
            case 9:
                if (!vehicle.IsMoving())
                {
                    vehicle.Forward(500);
                }

                if (!vehicle.IsMoving())
                {
                    state = 0;
                }
                break;
        }
    }

    bool IsFinished()
    {
        return (state == 0);
    }

    void Start()
    {
        if (IsFinished()) 
            state = 1;
    }
};



