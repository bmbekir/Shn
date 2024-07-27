#include "BNO055Process.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <DataLoader.h>
void printEvent(sensors_event_t *event);

void bnoGetData(Adafruit_BNO055 bno)
{
    sensors_event_t orientationData, angVelocityData, linearAccelData, magnetometerData, accelerometerData, gravityData;
    bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);
    bno.getEvent(&angVelocityData, Adafruit_BNO055::VECTOR_GYROSCOPE);
    bno.getEvent(&linearAccelData, Adafruit_BNO055::VECTOR_LINEARACCEL);
    bno.getEvent(&magnetometerData, Adafruit_BNO055::VECTOR_MAGNETOMETER);
    bno.getEvent(&accelerometerData, Adafruit_BNO055::VECTOR_ACCELEROMETER);
    bno.getEvent(&gravityData, Adafruit_BNO055::VECTOR_GRAVITY);

    // Print orientation data for debugging
    printEvent(&orientationData);
    printEvent(&angVelocityData);
    printEvent(&linearAccelData);
    printEvent(&magnetometerData);
    printEvent(&accelerometerData);
    printEvent(&gravityData);

    int8_t boardTemp = bno.getTemp();
    Serial.println();
    Serial.print("Temperature: ");
    Serial.println(boardTemp);

    uint8_t system, gyro, accel, mag = 0;
    bno.getCalibration(&system, &gyro, &accel, &mag);
    Serial.println();
    Serial.print("Calibration: Sys=");
    Serial.print(system);
    Serial.print(" Gyro=");
    Serial.print(gyro);
    Serial.print(" Accel=");
    Serial.print(accel);
    Serial.print(" Mag=");
    Serial.println(mag);

    Serial.println("--");
    delay(100);
}

void printEvent(sensors_event_t *event)
{
    double x = -1000000, y = -1000000, z = -1000000;
    if (event->type == SENSOR_TYPE_ACCELEROMETER)
    {
        Serial.print("Accl:");
        x = event->acceleration.x;
        y = event->acceleration.y;
        z = event->acceleration.z;
    }
    else if (event->type == SENSOR_TYPE_ORIENTATION)
    {
        Serial.print("Orient:");
        x = event->orientation.x;
        y = event->orientation.y;
        z = event->orientation.z;
    }
    else if (event->type == SENSOR_TYPE_MAGNETIC_FIELD)
    {
        Serial.print("Mag:");
        x = event->magnetic.x;
        y = event->magnetic.y;
        z = event->magnetic.z;
    }
    else if (event->type == SENSOR_TYPE_GYROSCOPE)
    {
        Serial.print("Gyro:");
        x = event->gyro.x;
        y = event->gyro.y;
        z = event->gyro.z;
    }
    else if (event->type == SENSOR_TYPE_ROTATION_VECTOR)
    {
        Serial.print("Rot:");
        x = event->gyro.x;
        y = event->gyro.y;
        z = event->gyro.z;
    }
    else if (event->type == SENSOR_TYPE_LINEAR_ACCELERATION)
    {
        Serial.print("Linear:");
        x = event->acceleration.x;
        y = event->acceleration.y;
        z = event->acceleration.z;
    }
    else if (event->type == SENSOR_TYPE_GRAVITY)
    {
        Serial.print("Gravity:");
        x = event->acceleration.x;
        y = event->acceleration.y;
        z = event->acceleration.z;
    }
    else
    {
        Serial.print("Unk:");
    }

    Serial.print("\tx= ");
    Serial.print(x);
    Serial.print(" |\ty= ");
    Serial.print(y);
    Serial.print(" |\tz= ");
    Serial.println(z);
}

BNO055Process::BNO055Process(TwoWire *wire)
{
    this->wire = wire;
}

BNO055Process::~BNO055Process()
{
}

int BNO055Process::run()
{
    sensors_event_t orientationData, angVelocityData, linearAccelData, magnetometerData, accelerometerData, gravityData;
    bno->getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);
    bno->getEvent(&angVelocityData, Adafruit_BNO055::VECTOR_GYROSCOPE);
    bno->getEvent(&linearAccelData, Adafruit_BNO055::VECTOR_LINEARACCEL);
    bno->getEvent(&magnetometerData, Adafruit_BNO055::VECTOR_MAGNETOMETER);
    bno->getEvent(&accelerometerData, Adafruit_BNO055::VECTOR_ACCELEROMETER);
    bno->getEvent(&gravityData, Adafruit_BNO055::VECTOR_GRAVITY);
    DataLoader::setOraData(orientationData.orientation.x, orientationData.orientation.y, orientationData.orientation.z);
    DataLoader::setAngData(angVelocityData.gyro.x, angVelocityData.gyro.y, angVelocityData.gyro.z);
    DataLoader::setLinData(linearAccelData.acceleration.x, linearAccelData.acceleration.y, linearAccelData.acceleration.z);
    DataLoader::setMagData(magnetometerData.magnetic.x, magnetometerData.magnetic.y, magnetometerData.magnetic.z);
    DataLoader::setAccData(accelerometerData.acceleration.x, accelerometerData.acceleration.y, accelerometerData.acceleration.z);
    DataLoader::setGraData(gravityData.acceleration.x, gravityData.acceleration.y, gravityData.acceleration.z);
    return 100;
}

int BNO055Process::init()
{
    this->bno = new Adafruit_BNO055(55, 0x28, this->wire);
    this->bno->begin();
    bno->setExtCrystalUse(true);
    return 1000;
}
