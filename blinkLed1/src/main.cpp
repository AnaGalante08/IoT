#include <Arduino.h>

#define PIN_LED 17
#define PIN_LEDVERMELHO 16 

void setup() {
  Serial.begin(115200);// velocidade de comunicação
  Serial.println("Hello, ESP32!");// console.log
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_LED1, OUTPUT);

}

void loop() {


digitalWrite(PIN_LED, LOW);
digitalWrite(PIN_LED1, HIGH);
delay(5000);


digitalWrite(PIN_LED1, LOW);
digitalWrite(PIN_LED, HIGH);
delay(5000);


}



