class Command_Move
{
    int direction = 0;
    int state = 0;

    AutomatedGuidedVehicle vehicle;
    Command_MoveForward cmd_moveForward(vehicle);
    Command_Dodge cmd_dodge(vehicle);
    Command_Rotate cmd_rotate(vehicle);

    public:

        void Command_Move(AutomatedGuidedVehicle obj)
        {
            vehicle = obj;
        }

        void Update()
        {
            switch (state)
            {
                case 1: 
                    if (cmd_moveForward.IsFinished())
                    {
                       Forward();
                    }

                    if (cmd_moveForward.IsFinished())
                    {
                        if (vehicle.Sensors.IsObjectDetected())
                        {
                            state = 2;
                        }

                        if (vehicle.Sensors.IsGroundDetected())
                        {
                            state = 3;
                        }
                    }

                    break;
                case 2:
                    if (cmd_dodge.IsFinished())
                    {
                        Dodge();
                    }

                    if (cmd_dodge.IsFinished())
                    {
                        state = 1;
                    }
                    break;

                case 3:
                    if (cmd_rotate.IsFinished())
                    {
                        if (direction == -1)
                        {
                            RotateLeft();
                        }
                        else if (direction == 1)
                        {
                            RotateRight();
                        }
                    }

                    if (cmd_rotate.IsFinished())
                    {
                        state = 4;
                    }
                    break;
                case 4:
                    if (cmd_rotate.IsFinished())
                    {
                        if (direction == -1)
                        {
                            RotateLeft();
                        }
                        else if (direction == 1)
                        {
                            RotateRight();
                        }
                    }

                    if (cmd_rotate.IsFinished())
                    {
                        state = 1;
                        direction = -direction;
                    }
                    break;
            }
            cmd_rotate.Update();
            cmd_dodge.Update();
            cmd_moveForward.Update();
        }

        void Start()
        {
            state = 1;
            direction = -1;
        }

        void Forward()
        {
            cmd_moveForward.Start();
        }

        void RotateLeft()
        {
            cmd_Rotate.Left();
        }

        void RotateRight()
        {
            cmd_Rotate.Right();
        }

        void Dodge()
        {
            cmd_Dodge.Start();
        }

        bool IsFinished()
        {
            return (state == 0);
        }
};