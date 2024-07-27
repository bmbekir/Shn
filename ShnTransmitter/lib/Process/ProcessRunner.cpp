#include "ProcessRunner.h"
#include <Arduino.h>
ProcessRunner::ProcessRunner(/* args */)
{
}

ProcessRunner::~ProcessRunner()
{
}

void ProcessRunner::run()
{
    ProcessItem *p;
    int ms = millis();
    for (int i = 0; i < this->processes.getSize(); i++)
    {
        p = this->processes.get(i);
        if (p->nextRunTime <= ms)
        {
            p->nextRunTime = ms + p->process->run();
        }
    }
}

void ProcessRunner::addProcess(IProcess *prc)
{
    long ms = millis();
    ProcessItem *p = new ProcessItem;
    p->nextRunTime = ms + prc->init();
    p->process = prc;
    this->processes.add(p);
}
