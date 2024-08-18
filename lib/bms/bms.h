#ifndef __BMS_H
#define __BMS_H

struct BMSData {
  int cellVoltages[32]; // Individual cell voltage
  int totalVoltage; // Total pack voltage
  int current; // Charge current
  int temperatures[6]; // Contact temperatures 1-6
  int soc; // State of charge (%)
  int soh; // State of health (%)
  int cycleCount; // Total pack cycles
  int protectionStatus[3]; // Primary, secondary, tertiary
  int balancingStatus[2]; // 1-16S, 17-32S
};

#endif