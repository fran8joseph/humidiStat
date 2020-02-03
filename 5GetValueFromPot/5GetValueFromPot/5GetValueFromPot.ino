
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

int potValue =0;

int potPin=A2;

const int buttonPin=2;
//pinMode(buttonPin,INPUT);
int buttonState=0; 

void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  lcd.begin(16, 1);
 // pinMode(buttonPin,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  potValue=analogRead(potPin);
  potValue=map(potValue,0,1023,0,100);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("potValue=");
  lcd.print(potValue);

  delay(1000);

//  buttonState = digitalRead(buttonPin);
//  lcd.clear();
//  lcd.setCursor(0, 0);
//  lcd.print("buttonState1=");
//  lcd.print(buttonState);
//
//  delay(1000);
  
//   if (buttonState == HIGH) {
//    // turn LED on:
//      lcd.clear();
//      lcd.print("buttonON");
//        delay(1000);
//           
//  } else if (buttonState == LOW) {
//    // turn LED off:
//      lcd.clear();
//      lcd.print("buttonOFF");
//        delay(1000);
//         //lcd.clear();
//  }

  //lcd.clear();
}
