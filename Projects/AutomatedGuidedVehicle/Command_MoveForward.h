class Command_MoveForward
{
    bool move = false;
    AutomatedGuidedVehicle _vehicle;

    public:

        void Command_MoveForward(AutomatedGuidedVehicle vehicle)
        {
            _vehicle = vehicle;
        }

        void Update()
        {
            if (!(vehicle.IsMoving()) && move)
            {
                vehicle.Forward(60000);
            }

            if (vehicle.Sensors.IsGroundDetected() || vehicle.Sensors.IsObjectDetected())
            {
                move = false;
                vehicle.Stop();
            }
        }

        void Start()
        {
            move = true;
        }

        void IsFinished()
        {
            return (!move);
        }
};