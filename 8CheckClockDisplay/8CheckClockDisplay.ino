#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

 int setHour=23;
 int setMin=58;

void setup() {
  // put your setup code here, to run once:
 //Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.begin(16, 1);
}

void loop() {
  // put your main code here, to run repeatedly:
    lcd.clear();
    lcd.setCursor(0, 0);


        for(int j=1; j<=60; j++){
              lcd.clear();
     lcd.setCursor(0, 0);

        if(j>59){
          setMin++;
        }
        if(setMin>59){
          setHour++;
          setMin=0;
        }
        if(setHour>23)
          setHour=0;
          
        if(setHour<10)
          lcd.print("0");
         lcd.print(setHour);
        lcd.print(":");
        if(setMin<10)
          lcd.print("0");
        lcd.print(setMin);
        lcd.print(":");
        if(j<10)
          lcd.print("0");
        if(j<60)  
          lcd.print(j);
         else
          lcd.print("00"); 
        delay(1000);
      }

}
