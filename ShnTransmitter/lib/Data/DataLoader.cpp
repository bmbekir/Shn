#include "DataLoader.h"
#include "Arduino.h"

Data data;
DataLoader::DataLoader(/* args */)
{
}

DataLoader::~DataLoader()
{
}

Data *DataLoader::getData()
{
    return &data;
}

void DataLoader::setTemperature(float value)
{
    data.general.temperature = value;
}

void DataLoader::setPressure(float value)
{
    data.general.pressure = value;
}

void DataLoader::setStepCount(int value)
{
    data.general.stepCount = value;
}

void DataLoader::setFireStatus(char status)
{
    data.general.fireStatus = status;
}

void DataLoader::setGpsData(float lat, float lng, int satCount)
{
    GpsData d;
    d.latitude = lat;
    d.longitude = lng;
    d.satCount = satCount;
    delete &data.gps;
    data.gps = d;
}

void DataLoader::setOraData(float x, float y, int z)
{
    GyroData d;
    d.x = x;
    d.y = y;
    d.z = z;
    delete &data.orientationData;
    data.orientationData = d;
}

void DataLoader::setAngData(float x, float y, int z)
{
    GyroData d;
    d.x = x;
    d.y = y;
    d.z = z;
    delete &data.angVelocityData;
    data.angVelocityData = d;
}

void DataLoader::setLinData(float x, float y, int z)
{
    GyroData d;
    d.x = x;
    d.y = y;
    d.z = z;
    delete &data.linearAccelData;
    data.linearAccelData = d;
}

void DataLoader::setMagData(float x, float y, int z)
{
    GyroData d;
    d.x = x;
    d.y = y;
    d.z = z;
    delete &data.magnetometerData;
    data.magnetometerData = d;
}

void DataLoader::setAccData(float x, float y, int z)
{
    GyroData d;
    d.x = x;
    d.y = y;
    d.z = z;
    delete &data.accelerometerData;
    data.accelerometerData = d;
}

void DataLoader::setGraData(float x, float y, int z)
{
    GyroData d;
    d.x = x;
    d.y = y;
    d.z = z;
    delete &data.gravityData;
    data.gravityData = d;
}
