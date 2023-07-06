//ARPIT PAUL PROJECT UART

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <esp_deep_sleep.h>

#define TX_PIN 17
#define RX_PIN 16    //config of pins...
#define BUTTON_PIN 15
#define BUILT_IN 2
SoftwareSerial uart(TX_PIN, RX_PIN); 

void setup() {
  Serial.begin(115200); 
  uart.begin(9600); 
  pinMode(BUTTON_PIN, INPUT_PULLUP);   //pinmode declaration...
  pinMode(BUILT_IN,OUTPUT);
   esp_sleep_enable_ext0_wakeup(GPIO_NUM_15,0);  //sleepmode wakeup trigger initialization...
}

void loop() {
  if (esp_sleep_get_wakeup_cause()==ESP_SLEEP_WAKEUP_EXT0) {

    digitalWrite(BUILT_IN,HIGH);   //Indication of wakeup...
    String dataToSend = "Hello, Arduino! I am ESP32!!"; 
    
    uart.println(dataToSend); 
    Serial.println("Data sent: " + dataToSend);

    unsigned long startTime = millis(); 
    bool dataReceived = false; 

    while (!dataReceived && millis() - startTime < 5000) { 
      if (uart.available()) { 
        String receivedData = uart.readString(); 
        Serial.println("Data received: " + receivedData);
        dataReceived = true; 
      }
    }

    if (!dataReceived) { 
      Serial.println("Error: No response received from Arduino.");
    }

    delay(1000); 
  }

 Serial.println("Going to sleep...");
  esp_deep_sleep_start();  //deepsleep mode on...

  //goodnight!, sweetdreams, zzz...
}
