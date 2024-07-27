#include "E32Process.h"
#include "Data.h"
#include "DataLoader.h"

E32Process::E32Process(byte txPin, byte rxPin, byte auxPin, byte m0Pin, byte m1Pin)
{
    this->e32ttl = new LoRa_E32(txPin, rxPin, auxPin, m0Pin, m1Pin);
}

E32Process::~E32Process()
{
    delete this->e32ttl;
}

int E32Process::init()
{
    e32ttl->begin();
    // After set configuration comment set M0 and M1 to low
    // and reboot if you directly set HIGH M0 and M1 to program
    ResponseStructContainer c;
    c = e32ttl->getConfiguration();
    Configuration configuration = *(Configuration *)c.data;
    configuration.ADDL = 1;
    configuration.ADDH = 0;
    configuration.CHAN = 23;
    configuration.OPTION.fixedTransmission = FT_FIXED_TRANSMISSION;
    e32ttl->setConfiguration(configuration, WRITE_CFG_PWR_DWN_SAVE);
    c.close();
    // ---------------------------
    return 0;
}

int E32Process::run()
{
    Data *data = DataLoader::getData();
    // Serial.println("Send Data Start");
    // Serial.print("Alt:");
    // Serial.println(data->altitude);
    // Serial.print("Lng:");
    // Serial.println(data->longitude);
    // Serial.print("Lat:");
    // Serial.println(data->latitude);
    // Serial.print("temp:");
    // Serial.println(data->temperature);
    // Serial.println("Send Data End");

    ResponseStatus rs = this->e32ttl->sendFixedMessage(0, 2, 23, data, sizeof(Data));
    rs.getResponseDescription();
    delete data;
    return 1000;
}
