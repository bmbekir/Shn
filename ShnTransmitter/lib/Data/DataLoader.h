#ifndef DATALOADER_H
#define DATALOADER_H
#include <Data.h>
class DataLoader
{
private:
    DataLoader(/* args */);
    ~DataLoader();

public:
    static Data *getData();
    static void setTemperature(float value);
    static void setPressure(float value);
    static void setStepCount(int value);
    static void setFireStatus(char status);
    static void setGpsData(float lat, float lng, int satCount);
    static void setOraData(float x, float y, int z);
    static void setAngData(float x, float y, int z);
    static void setLinData(float x, float y, int z);
    static void setMagData(float x, float y, int z);
    static void setAccData(float x, float y, int z);
    static void setGraData(float x, float y, int z);
};

#endif