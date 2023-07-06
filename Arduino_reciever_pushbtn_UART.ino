// ARPIT PAUL PROJECT UART

#include <Arduino.h>
#include <SoftwareSerial.h>


#define TX_PIN 6     //Tx pin Arduino
#define RX_PIN 5     //Rx pin Arduino

SoftwareSerial uart(TX_PIN, RX_PIN); 

void setup() {
  Serial.begin(115200); //starting serial monitor...
  uart.begin(9600);     //starting uart communication...
}

void loop() {
  if (uart.available()) { 
    String receivedData = uart.readString(); 
    Serial.println("Data received: " + receivedData);

    uart.println("Arduino recieve message!!"); 
  }
}

