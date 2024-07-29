#include <cstdint>
#include <Data.h>
#ifndef DATACONVERTER_H
#define DATACONVERTER_H

class DataConverter
{
private:
    /* data */
    DataConverter(/* args */);

public:
    static uint8_t *getDataBytes(void *structData, DATA_TYPE type, int &size);
    // static uint8_t *getDataBytes(GeneralData *data, int &size);
    // static uint8_t *getDataBytes(GpsData *data, int &size);
    // static uint8_t *getDataBytes(GyroData *data, DATA_TYPE type, int &size);
};

#endif