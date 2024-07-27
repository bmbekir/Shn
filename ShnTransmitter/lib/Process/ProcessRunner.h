#ifndef PROCESSLOADER_H
#define PROCESSLOADER_H
#include "IProcess.h"
#include <List.hpp>
class ProcessRunner
{
private:
    struct ProcessItem
    {
    public:
        int nextRunTime;
        IProcess *process;
    };
    /* data */
    List<ProcessItem *> processes;

public:
    ProcessRunner(/* args */);
    ~ProcessRunner();
    void run();
    void addProcess(IProcess *prc);
};
#endif
