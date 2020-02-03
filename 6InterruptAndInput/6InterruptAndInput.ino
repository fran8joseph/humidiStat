
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

int potValue =0;

int potPin=A2;

const int buttonPin=2;
volatile int setMinValue=20; 
volatile int setMaxValue=55; 
volatile int minMaxToggle=0; 

void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  lcd.begin(16, 1);
  pinMode(buttonPin,INPUT);

  attachInterrupt(digitalPinToInterrupt(buttonPin), setMinHumidity, LOW);

 // buttonState = digitalRead(buttonPin);
  }


void loop() {
  // put your main code here, to run repeatedly:
 /* potValue=analogRead(potPin);
  potValue=map(potValue,0,1023,0,100);
  */
  potValue=analogRead(potPin);
  potValue=map(potValue,0,1023,0,100);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("potValue=");
  lcd.print(potValue);

 // delay(5000);

   //buttonState = digitalRead(buttonPin);
//  lcd.clear();
//  lcd.setCursor(0, 0);
//  lcd.print("buttonState=");
//  lcd.print(buttonState);

  delay(500);

  
 
  lcd.clear();

  lcd.print("setValueInter=");
  lcd.print(setMinValue);
  delay(1000);

   lcd.clear();

  lcd.print("setMaxInter=");
  lcd.print(setMaxValue);
  delay(1000);
}

void setMinHumidity() {
  setMinValue=analogRead(potPin);
  setMinValue=map(setMinValue,0,1023,0,100);

}
