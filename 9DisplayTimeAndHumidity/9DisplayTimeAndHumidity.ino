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
int potValue = 0;
int potPin = A2;

int humidity;
int roomTemp;

 int firstTimeCheck =0;

volatile int setHour = 0;
volatile int setMin = 0;

const int minSetPin = 2;
const int maxSetPin = 3;

bool minButtonPress = false;
bool maxButtonPress = false;

bool timeMinSet = false;
bool timeHourSet = false;

volatile int setMinValue = 20;
volatile int setMaxValue = 50;


void setup() {

  int valuesSet = 0;
  int timeSet = 0;

  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.begin(16, 1);
  servo.attach(9, 590, 2300);


  while (timeSet != 2) {

    attachInterrupt(digitalPinToInterrupt(minSetPin), setTimeMin, LOW);
    attachInterrupt(digitalPinToInterrupt(maxSetPin), setTimeHour, LOW);

    lcd.clear();
    lcd.setCursor(0, 0);


    if (timeHourSet == true) {
      lcd.print("Set MIN");
      potValue = analogRead(potPin);
      potValue = map(potValue, 0, 1023, 0, 60);

    }
    else {
      lcd.print("Set HOURS");
      potValue = analogRead(potPin);
      potValue = map(potValue, 0, 1023, 0, 24);
    }


    lcd.setCursor(0, 1);
    lcd.print("pot=");
    lcd.print(potValue);

    delay(800);

    if (timeMinSet == true ||  timeHourSet == true)  {
      timeSet = 1;

      if (timeMinSet == true && timeHourSet == true) {
        timeSet = 2;
      }
    }
    else
      continue;

  }
  while (valuesSet != 2) {

    attachInterrupt(digitalPinToInterrupt(minSetPin), setMinHumidity, LOW);
    attachInterrupt(digitalPinToInterrupt(maxSetPin), setMaxHumidity, LOW);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Set Max_Min Humd");
    potValue = analogRead(potPin);
    potValue = map(potValue, 0, 1023, 0, 100);
    lcd.setCursor(0, 1);
    lcd.print("pot=");
    lcd.print(potValue);
    lcd.print("   Set=");
    lcd.print(valuesSet);
    delay(800);

    lcd.clear();

    if (minButtonPress == true ||  maxButtonPress == true)  {
      valuesSet = 1;

      if (minButtonPress == true && maxButtonPress == true) {
        valuesSet = 2;
      }
    }
    else
      continue;
  }
}

void loop() {

  int chk = DHT.read11(DHT11_PIN);
 

  humidity = DHT.humidity;
  roomTemp = DHT.temperature;


  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(roomTemp);
  lcd.print("\337C");
  //lcd.setCursor(0, 1);
  lcd.print("  H:");
  lcd.print(humidity);
  lcd.print("% ");
  if(firstTimeCheck==0)
    delay(800);

  lcd.clear();
  lcd.print("Min=");
  lcd.print(setMinValue);
  lcd.print("  Max=");
  lcd.print(setMaxValue);
  if(firstTimeCheck==0)
    delay(800);


  humidity = DHT.humidity;

  if ((setMinValue < setMaxValue) && (setMinValue != setMaxValue) && (setMaxValue <= 70)) {

    if (humidity <= setMinValue) {

      servo_pos = servo.read();

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Humidity lesser");
      if(firstTimeCheck==0)
        delay(500);

      if (servo_pos > 90) {
        servo.write(0);
      }
    }

    else if (humidity >= setMaxValue) {

      servo_pos = servo.read();
      lcd.clear();
      lcd.print("Humid higher");

      if (servo_pos < 100) {
        servo.write(180);
        delay(500);
      }

    }

  }

  else if (setMaxValue >= 70) {

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WARNING");

    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Humidity > 70%");
    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Dafault values set");
    delay(1000);
    setMinValue = 20;
    setMaxValue = 50;
  }

  else if (setMaxValue < setMinValue) {

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ERROR");

    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("MinVal > MaxVal");
    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Dafault values set");
    delay(1000);
    setMinValue = 20;
    setMaxValue = 50;
  }

  else {

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ERROR");

    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("MinVal = MaxVal");
    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Dafault values set");
    delay(1000);
    setMinValue = 20;
    setMaxValue = 50;
  }

  for (int j = 1; j <= 60; j++) {
    lcd.clear();
    lcd.setCursor(0, 0);

    if (j > 59) {
      setMin++;
    }
    if (setMin > 59) {
      setHour++;
      setMin = 0;
    }
    if (setHour > 23)
      setHour = 0;


    lcd.print("T:");
    lcd.print(roomTemp);
    lcd.print("\337C");
    lcd.print("    H:");
    lcd.print(humidity);
    lcd.print("%  ");
    lcd.setCursor(0, 1);
    if (setHour < 10)
      lcd.print("      0");
    lcd.print(setHour);
    lcd.print(":");
    if (setMin < 10)
      lcd.print("0");
    lcd.print(setMin);
    lcd.print(":");
    if (j < 10)
      lcd.print("0");
    if (j < 60)
      lcd.print(j);
    else
      lcd.print("00");

    if (setHour > 22 || setHour < 07) {
      lcd.noBacklight();
    }
    else
      lcd.backlight();

    delay(945);
  }

  firstTimeCheck+=1;

}


void setMinHumidity() {
  setMinValue = analogRead(potPin);
  setMinValue = map(setMinValue, 0, 1023, 0, 100);
  minButtonPress = true;


}

void setMaxHumidity() {
  setMaxValue = analogRead(potPin);
  setMaxValue = map(setMaxValue, 0, 1023, 0, 100);
  maxButtonPress = true;

}


void setTimeHour() {
  setHour = analogRead(potPin);
  setHour = map(setHour, 0, 1023, 0, 24);
  timeHourSet = true;

}


void setTimeMin() {
  setMin = analogRead(potPin);
  setMin = map(setMin, 0, 1023, 0, 60);
  timeMinSet = true;

}
