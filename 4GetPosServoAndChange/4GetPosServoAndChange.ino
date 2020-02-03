#include <dht.h>
#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>


#define DHT11_PIN A0

LiquidCrystal_I2C lcd(0x27, 20, 4);

Servo servo;

int servo_pos = 0;

dht DHT;


void setup() {

  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.begin(16, 1);
  servo.attach(9, 590, 2300);

}

void loop() {

  int chk = DHT.read11(DHT11_PIN);

  float humidity = DHT.humidity;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp ");
  lcd.print(DHT.temperature);
  lcd.print("\337C");
  lcd.setCursor(0, 1);
  lcd.print("Humd ");
  lcd.print(humidity);
  lcd.print("% ");
  delay(5000);


  if (humidity <= 40) {

    servo_pos = servo.read();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Humidity lesser");
    delay(5000);

    if (servo_pos > 90) {
      servo.write(0);
      }
  }

  else if (humidity >= 45) {

    servo_pos = servo.read();
    lcd.clear();
    lcd.print("Humid higher");

    if (servo_pos < 100) {
      servo.write(180);
      delay(1000);
    }

  }

  for (int j = 0; j < 150; j++) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Pacing : ");
      lcd.print(j);
      delay(1000);
    }
  
}
