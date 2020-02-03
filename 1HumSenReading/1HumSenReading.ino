#include <dht.h>


dht DHT;

#define DHT11_PIN A0

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.print(DHT.temperature);
  Serial.print(" C \n");
  Serial.print("Humidity = ");
  Serial.print(DHT.humidity);
  Serial.print("% \n");
  delay(5000);
}
