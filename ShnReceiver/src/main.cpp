
#include "Arduino.h"
#include "LoRa_E32.h"
SoftwareSerial mySerial(2, 3); // Arduino RX <-- e32 TX, Arduino TX --> e32 RX

LoRa_E32 e32ttl(&mySerial);

void printParameters(struct Configuration configuration);
void printModuleInformation(struct ModuleInformation moduleInformation);
// The setup function is called once at startup of the sketch
void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB
  }
  delay(100);

  e32ttl.begin();

  //	e32ttl.resetModule();
  // After set configuration comment set M0 and M1 to low
  // and reboot if you directly set HIGH M0 and M1 to program
  ResponseStructContainer c;
  c = e32ttl.getConfiguration();
  Configuration configuration = *(Configuration *)c.data;
  configuration.ADDL = 2;
  configuration.ADDH = 0;
  configuration.CHAN = 23;
  configuration.OPTION.fixedTransmission = FT_FIXED_TRANSMISSION;

  e32ttl.setConfiguration(configuration, WRITE_CFG_PWR_DWN_SAVE);
  printParameters(configuration);
  c.close();
  // ---------------------------
  Serial.println();
  Serial.println("Start listening!");
  e32ttl.setMode(MODE_2_POWER_SAVING);
}
struct Data
{
  float temperature;
  float pressure;
  float longitude;
  float latitude;
  float satCount;
  float altitude;
  float originX;
  float originY;
  float originZ;
  float stepCount;
  char fireStatus;
};

// The loop function is called in an endless loop
void loop()
{
  int dataSize = e32ttl.available();
  if (dataSize > 1)
  {

    Serial.print("Data Size:");
    Serial.println(dataSize);
    ResponseStructContainer rsc = e32ttl.receiveMessage(sizeof(Data));
    struct Data message = *(Data *)rsc.data;

    Serial.print("Temp:");
    Serial.println((message.temperature));
    Serial.print("Pre:");
    Serial.println(message.pressure);
    Serial.print("Lat:");
    Serial.println(message.latitude);
    Serial.print("Lng:");
    Serial.println(message.longitude);
    Serial.print("Alt:");
    Serial.println(message.altitude);
    Serial.print("X:");
    Serial.println(message.originX);
    Serial.print("Y:");
    Serial.println(message.originY);
    Serial.print("Z:");
    Serial.println(message.originZ);
    Serial.print("sat:");
    Serial.println(message.satCount);
    Serial.print("FS:");
    Serial.println(message.fireStatus);
    Serial.print("STP:");
    Serial.println(message.stepCount);
    //			free(rsc.data);
    rsc.close();
  }
}

void printParameters(struct Configuration configuration)
{
  Serial.println("----------------------------------------");

  Serial.print(F("HEAD : "));
  Serial.print(configuration.HEAD, BIN);
  Serial.print(" ");
  Serial.print(configuration.HEAD, DEC);
  Serial.print(" ");
  Serial.println(configuration.HEAD, HEX);
  Serial.println(F(" "));
  Serial.print(F("AddH : "));
  Serial.println(configuration.ADDH, DEC);
  Serial.print(F("AddL : "));
  Serial.println(configuration.ADDL, DEC);
  Serial.print(F("Chan : "));
  Serial.print(configuration.CHAN, DEC);
  Serial.print(" -> ");
  Serial.println(configuration.getChannelDescription());
  Serial.println(F(" "));
  Serial.print(F("SpeedParityBit     : "));
  Serial.print(configuration.SPED.uartParity, BIN);
  Serial.print(" -> ");
  Serial.println(configuration.SPED.getUARTParityDescription());
  Serial.print(F("SpeedUARTDatte  : "));
  Serial.print(configuration.SPED.uartBaudRate, BIN);
  Serial.print(" -> ");
  Serial.println(configuration.SPED.getUARTBaudRate());
  Serial.print(F("SpeedAirDataRate   : "));
  Serial.print(configuration.SPED.airDataRate, BIN);
  Serial.print(" -> ");
  Serial.println(configuration.SPED.getAirDataRate());

  Serial.print(F("OptionTrans        : "));
  Serial.print(configuration.OPTION.fixedTransmission, BIN);
  Serial.print(" -> ");
  Serial.println(configuration.OPTION.getFixedTransmissionDescription());
  Serial.print(F("OptionPullup       : "));
  Serial.print(configuration.OPTION.ioDriveMode, BIN);
  Serial.print(" -> ");
  Serial.println(configuration.OPTION.getIODroveModeDescription());
  Serial.print(F("OptionWakeup       : "));
  Serial.print(configuration.OPTION.wirelessWakeupTime, BIN);
  Serial.print(" -> ");
  Serial.println(configuration.OPTION.getWirelessWakeUPTimeDescription());
  Serial.print(F("OptionFEC          : "));
  Serial.print(configuration.OPTION.fec, BIN);
  Serial.print(" -> ");
  Serial.println(configuration.OPTION.getFECDescription());
  Serial.print(F("OptionPower        : "));
  Serial.print(configuration.OPTION.transmissionPower, BIN);
  Serial.print(" -> ");
  Serial.println(configuration.OPTION.getTransmissionPowerDescription());

  Serial.println("----------------------------------------");
}
void printModuleInformation(struct ModuleInformation moduleInformation)
{
  Serial.println("----------------------------------------");
  Serial.print(F("HEAD BIN: "));
  Serial.print(moduleInformation.HEAD, BIN);
  Serial.print(" ");
  Serial.print(moduleInformation.HEAD, DEC);
  Serial.print(" ");
  Serial.println(moduleInformation.HEAD, HEX);

  Serial.print(F("Freq.: "));
  Serial.println(moduleInformation.frequency, HEX);
  Serial.print(F("Version  : "));
  Serial.println(moduleInformation.version, HEX);
  Serial.print(F("Features : "));
  Serial.println(moduleInformation.features, HEX);
  Serial.println("----------------------------------------");
}