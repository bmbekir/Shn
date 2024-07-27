#ifndef DATA_H
#define DATA_H

struct GeneralData
{
    float temperature;
    float pressure;
    float altitude;
    float stepCount;
    char fireStatus;
};

struct GpsData
{
    float longitude;
    float latitude;
    float satCount;
};

struct GyroData
{
    float x;
    float y;
    float z;
};

struct Data
{
    GeneralData general;
    GpsData gps;
    GyroData orientationData;
    GyroData angVelocityData;
    GyroData linearAccelData;
    GyroData magnetometerData;
    GyroData accelerometerData;
    GyroData gravityData;
};

enum DATA_TYPE
{
    GNL_DATA_TYPE = 1,
    GPS_DATA_TYPE = 2,
    ORA_DATA_TYPE = 3,
    ANG_DATA_TYPE = 4,
    LIN_DATA_TYPE = 5,
    MAG_DATA_TYPE = 6,
    ACC_DATA_TYPE = 7,
    GRA_DATA_TYPE = 8,
};

#endif