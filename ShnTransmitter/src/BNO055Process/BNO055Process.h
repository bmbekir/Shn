#ifndef BNO055_H
#define BNO055_H
#include <IProcess.h>
#include <Adafruit_BNO055.h>
#include <Wire.h>

class BNO055Process : public IProcess
{
private:
    TwoWire *wire;
    Adafruit_BNO055 *bno;

public:
    BNO055Process(TwoWire *wire);
    ~BNO055Process();
    int init() override;
    int run() override;
};

#endif