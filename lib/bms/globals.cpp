#include <HardwareSerial.h>
#include "bms.h"

BMSData bmsData;

HardwareSerial BMSSerial(1); // RX, TX (Connect to BMS UART)