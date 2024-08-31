#ifndef __GLOBALS_H
#define __GLOBALS_H
#include "bms.h"

#define HW_UUID ESP.getEfuseMac()
#define HW_UUID_8 (uint8_t)HW_ID


#define HW_NAME "ESP32-BMS-Bridge"
#define FW_VERSION_MAJOR 0
#define FW_VERSION_MINOR 1

extern BMSData bmsData; 
extern HardwareSerial BMSSerial;

#endif