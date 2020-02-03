#include <dht.h>
#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


#define DHT11_PIN A0
LiquidCrystal_I2C lcd(0x27,20,4); 

dht DHT;


void setup() {

  Serial.begin(9600);
  lcd.init();   
   lcd.backlight();
  lcd.begin(16, 1);
}

void loop() {
 
  int chk = DHT.read11(DHT11_PIN);
 

  lcd.setCursor(0, 0);
  lcd.print("Temp ");
  lcd.print(DHT.temperature);
  lcd.print("\337C");
  lcd.setCursor(0, 1);
  lcd.print("Humd ");
  lcd.print(DHT.humidity);
  lcd.print("% ");
  delay(5000);
}
