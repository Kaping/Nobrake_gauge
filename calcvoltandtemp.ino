#include <OneWire.h>

#define in3 3
#define in4 4
#define pwd 5
#define in2 6
//3,4번 핀을 모터핀으로 

OneWire  ds(2);  // on pin 10 (a 4.7K resistor is necessary)



float input_vol;
float cal_vol;
float celsius;

void setup() {
  pinMode(A1, INPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(pwd, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  CalculateVoltage();
  CalculateTemperature();
  TempToMotorSpeed();

 Serial.println(celsius); //온도
 delay(00);
 
}

void Motor(int speed_power) //speed power : 0~255 가능
{
  if (speed_power == 0)
  {
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    analogWrite(in2, 0);
  }
  else
  {
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(in2, speed_power);
    analogWrite(pwd, speed_power);
  }
}

void TempToMotorSpeed(){
  int temp = map(celsius - 23, 0, 10, 0, 105);
  if(celsius > 23) //23도 이상
    {
      if((temp + 150) >= 255)
        Motor(255);        //최대 속도
      else
        Motor(150 + temp); //기본 동작 + 온도 따라 성능이 올라감
    }
  else
    Motor(0); //모터 off
}

void CalculateVoltage(){
  float tempp;
  input_vol = analogRead(A1);
  tempp = input_vol/4.092;
  cal_vol = tempp/10;
}

void CalculateTemperature(){
  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
  float fahrenheit;
  
  if ( !ds.search(addr)) {
    ds.reset_search();
    delay(250);
    return;
  }
  for( i = 0; i < 8; i++) {
  }

  if (OneWire::crc8(addr, 7) != addr[7]) {
      return;
  }
 
  // the first ROM byte indicates which chip
  switch (addr[0]) {
    case 0x10:
      type_s = 1;
      break;
    case 0x28:
      type_s = 0;
      break;
    case 0x22:
      type_s = 0;
      break;
    default:
      return;
  } 

  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);        // start conversion, with parasite power on at the end
  
  delay(1000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.
  
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad

  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
  }
  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
  
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
   
  }
  celsius = (float)raw / 16.0;
  fahrenheit = celsius * 1.8 + 32.0;

   
}
