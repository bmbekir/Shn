#ifndef IPROCESS_H
#define IPROCESS_H

class IProcess
{

public:
    virtual int run() = 0;
    virtual int init() = 0;
};
#endif