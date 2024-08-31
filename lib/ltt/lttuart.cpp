#include <Arduino.h>
#include <HardwareSerial.h>
#include "crc.h"
#include "globals.h"

// Function to read battery cell voltages and related data
void readBatteryCellVoltages() {
   // Construct the Modbus request to read registers 0xD000 to 0xD025 (62 registers = 124 bytes)
  uint8_t request[] = {0x01, 0x03, 0xD0, 0x00, 0x00, 0x26, 0xFC, 0xD0}; 
  BMSSerial.write(request, sizeof(request));

  // Read and process the response
  if (BMSSerial.available() >= 7 + 124) { 
    uint8_t response[7 + 124];
    BMSSerial.readBytes(response, sizeof(response));

    // Verify CRC 
    unsigned int calculated_crc = CRC16RTU(response, 7 + 124 - 2); // Exclude the last two bytes (CRC)
    unsigned int received_crc = (response[7 + 124 - 1] << 8) | response[7 + 124 - 2]; 
    if (calculated_crc != received_crc) {
      Serial.println("CRC error in readBatteryVoltages!");
      return; // Or handle the error appropriately
    }

    // Extract cell voltages
    for (int i = 0; i < 32; i++) {
      bmsData.cellVoltages[i] = (response[3 + i * 2] << 8) | response[4 + i * 2];
    }

    // Extract other data
    bmsData.totalVoltage = (response[3 + 34 * 2] << 8) | response[4 + 34 * 2];         // 0xD01A
    int maxCellVoltage = (response[3 + 40 * 2] << 8) | response[4 + 40 * 2];  // 0xD020
    int minCellVoltage = (response[3 + 41 * 2] << 8) | response[4 + 41 * 2];  // 0xD021
    int highestVoltageCellPosition = (response[3 + 42 * 2] << 8) | response[4 + 42 * 2]; // 0xD022
    int lowestVoltageCellPosition = (response[3 + 43 * 2] << 8) | response[4 + 43 * 2];  // 0xD023
    int voltageDifference = (response[3 + 44 * 2] << 8) | response[4 + 44 * 2];          // 0xD024

    // You can print or use these extracted values as needed
    // ...
  } else {
    log_i("Incomplete or no response in readBatteryVoltages");
  }
}

// Function to read battery temperatures and current information
void readBatteryTemperatureAndCurrent() {
  // Construct the Modbus request to read registers 0xD001 to 0xD013 (19 registers = 38 bytes)
  uint8_t request[] = {0x01, 0x03, 0xD0, 0x01, 0x00, 0x13, 0x2C, 0xC1};
  BMSSerial.write(request, sizeof(request));

  // Read and process the response
  if (BMSSerial.available() >= 7 + 38) {
    uint8_t response[7 + 38];
    BMSSerial.readBytes(response, sizeof(response));

    // Verify CRC 
    unsigned int calculated_crc = CRC16RTU(response, 7 + 38 - 2); // Exclude the last two bytes (CRC)
    unsigned int received_crc = (response[7 + 38 - 1] << 8) | response[7 + 38 - 2]; 
    if (calculated_crc != received_crc) {
      Serial.println("CRC error in readBatteryTemperatureAndCurrent!");
      return; // Or handle the error appropriately
    }

    // Extract contact temperatures 1-6
    for (int i = 0; i < 6; i++) {
      bmsData.temperatures[i] = ((response[3 + i * 2] << 8) | response[4 + i * 2] - 400) / 10; 
    }

    // Extract environment temperatures 1-3
    for (int i = 0; i < 3; i++) {
      // bmsData.environmentTemperatures[i] = ((response[3 + 6 * 2 + i * 2] << 8) | response[4 + 6 * 2 + i * 2] - 400) / 10;
    }

    // Extract heatsink temperature
    // bmsData.heatsinkTemperature = ((response[3 + 9 * 2] << 8) | response[4 + 9 * 2] - 400) / 10;

    // Extract maximum and minimum temperatures
    // maxTemperature = ((response[3 + 10 * 2] << 8) | response[4 + 10 * 2] - 400) / 10;
    // minTemperature = ((response[3 + 11 * 2] << 8) | response[4 + 11 * 2] - 400) / 10;

    // Extract charging and discharging current
    bmsData.current = ((response[3 + 12 * 2] << 8) | response[4 + 12 * 2]) / 10;
    // dischargingCurrent = ((response[3 + 13 * 2] << 8) | response[4 + 13 * 2]) / 10;

    // Extract SOC
    bmsData.soc = ((response[3 + 14 * 2] << 8) | response[4 + 14 * 2]);
  } else {
      log_i("Incomplete or no response in readBatteryVoltages");
  }
}