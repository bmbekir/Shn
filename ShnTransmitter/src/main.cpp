
#include "Arduino.h"
#include <SPI.h>
#include <ProcessRunner.h>
#include <E32Process/E32Process.h>
#include <BNO055Process/BNO055Process.h>
#include "./../definations.h"
#include <DataLoader.h>
ProcessRunner *runner;
E32Process *e32;
BNO055Process *bno;
void setup()
{
    Serial.begin(9600);
    delay(100);
    runner = new ProcessRunner();
    e32 = new E32Process(E32_TX_PIN, E32_RX_PIN, E32_AU_PIN, E32_M0_PIN, E32_M1_PIN);
    bno = new BNO055Process(&Wire);
    runner->addProcess(bno);
    runner->addProcess(e32);
    DataLoader::setTemperature(12);
    DataLoader::setFireStatus('A');
    DataLoader::setGpsData(0, 0, 0);
    DataLoader::setOraData(0, 0, 0);
    DataLoader::setPressure(0);
    DataLoader::setStepCount(77);
}
void loop()
{
    runner->run();
    bno->run();
}
