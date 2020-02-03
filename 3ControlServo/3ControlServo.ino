#include <dht.h>
#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>


#define DHT11_PIN A0

LiquidCrystal_I2C lcd(0x27,20,4); 

Servo servo;

int servo_pos=0;


dht DHT;


void setup() {

  Serial.begin(9600);
  lcd.init();   
   lcd.backlight();
  lcd.begin(16, 1);
  servo.attach(7);

  pinMode(7,OUTPUT);
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

//  for(servo_pos=0;servo_pos<=180;servo_pos+=1){
//    servo.write(servo_pos);
//    delay(10);
//  }
//
//  for(servo_pos=180;servo_pos>=1;servo_pos-=5){
//    servo.write(servo_pos);
//    delay(10);
//  }

 float humidity = DHT.humidity;

  if(humidity <=45){

    for(servo_pos=0;servo_pos<=40;servo_pos+=1){
      servo.write(servo_pos);
      delay(10);
    }
     
     humidity=DHT.humidity;

      delay(5000);
    }
      
  else if(humidity>=52){
    
    for(servo_pos=40;servo_pos>=140;servo_pos-=2){
      servo.write(servo_pos);
      delay(10);
    }
  }
 
}
