 #include <Arduino.h>
 #include <DHT.h>

const int DHTPin = 15;

DHT dht(DHTPin, DHT22);

void setup()
{
  Serial.begin(9600);

  dht.begin();
}

void loop()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  Serial.print("Umidade: ");
  Serial.println(h);
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println(" *C");

  delay(2000);
}