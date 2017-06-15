class Command_MoveToMat
{
    int state = 0;
    AutomatedGuidedVehicle _vehicle;

    public:

        void Command_MoveToMat(AutomatedGuidedVehicle vehicle)
        {
            _vehicle = vehicle;
        }

        void Update()
        {
            if (state == 0)
                return;

            if (_time % 100 != 0)
                return;
                
            switch(state)
            {
                case 1:
                    if (!vehicle.IsMoving())
                        vehicle.Forward(60000);

                    if (Sensors.IsDetected())
                        state++;
                    break;
                case 2:
                    if (/* IMU.Leveled */true)
                    {
                        vehicle.Stop();
                        state = 0;
                    }
                    break;
            }
        }

        void IsFinished()
        {
            return (state == 0)
        }

        void Start()
        {
            if (!IsFinished()) 
                state = 1;
        }
};