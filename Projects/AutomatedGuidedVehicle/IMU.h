#ifndef InternalMeasurementUnit_h // If Class is not defined, then define it and use underlying code (Double Usage)
#define InternalMeasurementUnit_h

class InternalMeasurementUnit
{
    public:
    float gForceX, gForceY, gForceZ;
    float rotX, rotY, rotZ;

    float TotalRotationZ;
    int address = 0b1101000;

    bool IsLevel()
    {
        return(gForceZ >= 1);
    }

    void ResetZ()
    {
        TotalRotationZ = 0;
    }
};

#endif // InternalMeasurementUnit_h
