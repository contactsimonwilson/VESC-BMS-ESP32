#include <Arduino.h>
#include <HardwareSerial.h>
#include "lttuart.h"
#include "globals.h"

int messageLength = 0;
uint8_t messageBuffer[1000];

static const char* TAG = "VESCBMS";

void setup() {
   // Set up serial connection
   BMSSerial.begin(9600, SERIAL_8N1, 20, 21, false); // Adjust pins (RX, TX) and baud rate as needed
   log_i("Init complete");
}

void readBmsData() {
   readBatteryCellVoltages();
   readBatteryTemperatureAndCurrent();
}

void sendBmsDataToVesc() {
  // Construct VESC CAN messages based on the BMS data
  // Send the VESC CAN messages
  // ...
}

void receiveVescCommands() {
  // Check for incoming CAN messages
  // If a VESC command is received, process it accordingly
  // ...
}

void loop() {
   // Read BMS data from UART
   readBmsData();
   // Send BMS data over CAN bus using VESC protocol
   sendBmsDataToVesc();
   // Receive and process VESC commands from CAN bus
   receiveVescCommands();
   delay(100);
}