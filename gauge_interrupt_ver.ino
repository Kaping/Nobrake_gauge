#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

hd44780_I2Cexp lcd;

const byte interruptPin = 2;
int count = 0;
int rpm = 0;
float velocity = 0;
float diameter = 0.5;

void setup() {
  Serial.begin(9600);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, FALLING);
  
  lcd.begin(16, 2); 
  lcd.clear();
  lcd.setCursor (0,0);
  lcd.print("Nobrake");
  lcd.setCursor (0,1);
  lcd.print("electric team"); 
  delay(3000);
}

void loop() {
  Serial.println(count);
  rpm = count*60;
  velocity = count*3.6*diameter*3.141592;  
  lcd.clear();
  lcd.setCursor (0,0);
  lcd.print("RPM : ");
  lcd.print(rpm);
  lcd.setCursor (0,1);
  lcd.print("VELOCITY : "); 
  lcd.print(velocity);
  count = 0;
  delay(1000);
}

void blink(){
  count++;
}
