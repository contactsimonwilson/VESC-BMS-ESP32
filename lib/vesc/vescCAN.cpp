#include <Arduino.h>
#include <ESP32-TWAI-CAN.hpp>


// CAN Setup (adjust pins if needed)
#define CAN_RX_PIN GPIO_NUM_16 
#define CAN_TX_PIN GPIO_NUM_17
#define CAN_SPEED 500 // kbps

void initCAN() {
    // Set pins
	ESP32Can.setPins(CAN_TX_PIN, CAN_RX_PIN);
	
    // You can set custom size for the queues - those are default
    ESP32Can.setRxQueueSize(5);
	ESP32Can.setTxQueueSize(5);

    // .setSpeed() and .begin() functions require to use TwaiSpeed enum,
    // but you can easily convert it from numerical value using .convertSpeed()
    ESP32Can.setSpeed(ESP32Can.convertSpeed(CAN_SPEED));

    // You can also just use .begin()..
    if(ESP32Can.begin()) {
        Serial.println("CAN bus started!");
    } else {
        Serial.println("CAN bus failed!");
    }

    // or override everything in one command;
    // It is also safe to use .begin() without .end() as it calls it internally
    if(ESP32Can.begin(ESP32Can.convertSpeed(500), CAN_TX_PIN, CAN_RX_PIN, 10, 10)) {
        Serial.println("CAN bus started!");
    } else {
        Serial.println("CAN bus failed!");
    }
    
}