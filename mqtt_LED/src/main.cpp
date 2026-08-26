#include <Arduino.h>
#include <WiFiClientSecure.h> //Broker com user e senha + conexão segura (TLS/SSL)
#include <PubSubClient.h> /// Biblioteca para comunição de MQTT
#include <ArduinoJson.h>// // Biblioteca para manipulação de JSON
#include <ESP8266WiFi.h>


// Configurações da Rede WiFi (Altere para os seus dados)
const char* ssid = "profbru";
const char* password = "12345678";


// Configurações do MQTT
const char* mqtt_server = "d895a66657a84666a1d0f741b27e2be8.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;
const char* mqtt_user = "mario";
const char* mqtt_password = "senai123";
const char* mqtt_topic = "carol/yas/led"; // #1 alteracao que deve ser feita: Topico unico


const int LED_PIN = D2; // Pino do LED embutido no ESP32


WiFiClientSecure espClient;
PubSubClient client(espClient);


void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);


  WiFi.begin(ssid, password);


  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }


  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP());
 
  // Essencial para a porta 8883 (TLS/SSL) no HiveMQ
  // Ignora a verificação do certificado raiz para simplificar o código
  espClient.setInsecure();
}


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem recebida no tópico: ");
  Serial.println(topic);


  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, payload, length);


  if (error) {
    Serial.print("Falha ao processar o JSON: ");
    Serial.println(error.c_str());
    return;
  }


  // Extrai o valor associado à chave "comando"
  const char* comando = doc["comando"];
 
  if (comando != nullptr) {
    if (String(comando) == "ligar") {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("Ação: LED Ligado");
    } else if (String(comando) == "desligar") {
      digitalWrite(LED_PIN, LOW);
      Serial.println("Ação: LED Desligado");
    }
  }
}


void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conexão MQTT...");
   
    // Cria um Client ID aleatório
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
   
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_password)) {
      Serial.println("Conectado!");
     
      // Inscreve no tópico logo após conectar
      client.subscribe(mqtt_topic);
      client.subscribe("2dtm/led");
    } else {
      Serial.print("Falhou, código de erro: ");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}


void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
 
  Serial.begin(115200);
 
  setup_wifi();
 
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}


void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
