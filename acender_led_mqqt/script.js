 const btnLigar = document.getElementById("btnLigar");

 const btnDesligar = document.getElementById("btnDesligar");

 const status = document.getElementById("status");


 // =========================================================================
// CONFIGURAÇÕES DO BROKER MQTT (Baseado no seu código C++)
// Nota: Para navegadores, usamos WebSockets. No HiveMQ Cloud, a porta é 8884.
// =========================================================================
let mqttClient = null;
const MQTT_SERVER = "d895a66657a84666a1d0f741b27e2be8.s1.eu.hivemq.cloud";
const MQTT_PORT = 8884;
const MQTT_USER = "mario";
const MQTT_PASSWORD = "senai123";
const TOPIC_LED_CONTROL = "labCarolYas";

// Gerar um ID de cliente aleatório para a página web
const clientId = "WebClient-" + Math.random().toString(16).substr(2, 8);

// Configura e conecta ao Broker MQTT
function connectMQTT() {
 mqttClient = new Paho.MQTT.Client(MQTT_SERVER, MQTT_PORT, clientId);

 mqttClient.onConnectionLost = function (responseObject) {
  if (responseObject.errorCode !== 0) {
   console.log("Conexão MQTT perdida: " + responseObject.errorMessage);
   setTimeout(connectMQTT, 5000); // Tentar reconectar após 5 segundos
  }
 };

 const options = {
  userName: MQTT_USER,
  password: MQTT_PASSWORD,
  useSSL: true, // Importante para o HiveMQ Cloud
  onSuccess: function () {
   console.log("Conectado ao MQTT Broker!");
  },
  onFailure: function (message) {
   console.log("Falha ao conectar: " + message.errorMessage);
   setTimeout(connectMQTT, 5000);
  },
 };

 console.log("Conectando ao broker...");
 mqttClient.connect(options);
}

function acenderLed()
{
    console.log("Ligou")
const payload = JSON.stringify({comando: "LIGAR"});

const mensagem = new Paho.MQTT.Message(payload);

mensagem.destinationName = TOPIC_LED_CONTROL;

mqttClient.send(mensagem);
}

function desligarLed()
{
        console.log("desLigou")

    
const payload = JSON.stringify({comando: "DESLIGAR"});

const mensagem = new Paho.MQTT.Message(payload);

mensagem.destinationName = TOPIC_LED_CONTROL;

mqttClient.send(mensagem);
}


btnLigar.addEventListener('click', acenderLed)
btnDesligar.addEventListener("click", desligarLed)


window.onload = function()
{
    connectMQTT();
};