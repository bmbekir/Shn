#ifndef E32PROCESS_H
#define E32PROCESS_H
#include <cstddef>
#include "LoRa_E32.h"
#include <IProcess.h>

class E32Process : public IProcess
{
private:
    LoRa_E32 *e32ttl;

public:
    E32Process(byte txPin, byte rxPin, byte aux, byte m0, byte m1);
    ~E32Process();
    int init() override;
    int run() override;
};

#endif