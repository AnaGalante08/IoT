#include <Arduino.h>
const int pinoLed = D2;
const int pinoBotao = D8;
const int pinoLedV = D11;
int estadoBotao = 0;



void setup() {
  // Configura a velocidade de comunicação
Serial.begin(115200);
//OUTPUT = Saida de dados // Input = Entrada de dados // Input_pullup = Entrada de dados de pulso
pinMode(pinoLed, OUTPUT);
pinMode(pinoBotao, INPUT_PULLUP);
pinMode(pinoLedV, OUTPUT);

//Garante que o LED inicia desligado
digitalWrite(pinoLed, LOW);
digitalWrite(pinoLedV,HIGH);

//Msg de inicialização
Serial.println("Sistema iniciado, pressione o botão para acender o LED");
}

void loop() {
  //Guarda o estado atual do botão,lido pela DIGITALREAD
  estadoBotao = digitalRead(pinoBotao);



  //Se o botão estiver pressionado, liga o LED
  if (estadoBotao == LOW)
  {
    
digitalWrite(pinoLed, HIGH);
Serial.println("Botão Pressionado, LED Ligado!");
digitalWrite(pinoLedV,LOW);
Serial.println("Botão Presionado, LED Vermelho Ligado! ");

  }else{
    digitalWrite(pinoLed, LOW);
    digitalWrite(pinoLedV, HIGH);
  }
  
//Debounce - Atraso proposital
delay(50);

}

