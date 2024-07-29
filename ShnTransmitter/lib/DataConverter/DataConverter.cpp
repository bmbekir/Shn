#include "DataConverter.h"
#include "../definations.h"
#include <stdlib.h>

DataConverter::DataConverter(/* args */)
{
}

uint8_t *DataConverter::getDataBytes(void *structData, DATA_TYPE type, int &size)
{
    char *verificationCode = VERIFY_CODE;
    int totalSize = sizeof(VERIFY_CODE) + size;
    uint8_t *data = (uint8_t *)calloc(totalSize, sizeof(uint8_t));
    size_t count = sizeof(VERIFY_CODE) - 1;
    int start = 0;
    for (size_t i = 0; i < count; i++)
    {
        data[i + start] = verificationCode[i];
    }
    start = count;
    data[start] = (uint8_t)type;
    count = size;
    for (size_t i = 0; i < count; i++)
    {
        data[i + start] = ((uint8_t *)structData)[i];
    }
    size = totalSize;
    return data;
}
