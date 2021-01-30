#include <LiquidCrystal_I2C.h>
/*
 * NoBrake의 자동차에 쓰일 계기판의 프로그램 입니다.
 
 * #define 뒤에 있는 값을 조정하여 임의로 간단한 수치변화를 할 수 있습니다.
 
 * 속력(km/h) =  { 타이어 원주(mm) / (홀센서 나중 측정시간 - 홀센서 처음 측정 시간) }
  
 * 궁금하신 점 있으시면 염수형한테 갠톡이나 디스코드 dm 해주세여
*/


  //타이어 직경, 맞는 핀의 값을 수정하여 조정하세요
#define WHEEL_MM 200

  //센서 핀번호, 맞는 핀의 값을 수정하여 조정하세요
#define HALL_SENSOR_PIN 3       //홀센서 핀 번호
#define CURRENT_SENSOR_PIN A0   //전류센서 핀


LiquidCrystal_I2C lcd(0x27, 20, 4); //lcd 선언, 도트 수에 따라 수정하세요


unsigned long TimeSet = 0; //아두이노의 절대시간
unsigned long First_Check = 0;
unsigned long Second_Check = 0;
boolean check_speed false;

char Car_Speed = 0; //차의 속도
int RPM = 0;        //RPM

void setup() {
 pinMode(HALL_SENSOR_PIN, INPUT);
 pinMode(CURRENT_SENSOR_PIN, INPUT);
 
 lcd.clear(); //최초 lcd 화면 초기화
}

void loop() {
  TimeSet = millis();

  if(digitalRead(HALL_SENSOR_PIN) == HIGH && check_speed = false) //최초 신호 감지
  {
    First_Check = TimeSet;
    check_speed = true;
  }
  if(digitalRead(HALL_SENSOR_PIN) == HIGH && check_speed = true) //한바퀴 돌고 두 번째 신호 감지 > 속도측정
  {
    Second_Check = TimeSet;
    check_speed = false;

    RPM = ((Second_Check - first_Check)/1000)
    Car_Speed = (WHEEL_MM * 1000000) / ((Second_Check - first_Check)*3.6); // km/h단위
  }

}
