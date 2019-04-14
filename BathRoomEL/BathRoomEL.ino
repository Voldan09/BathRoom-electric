#include "timer-api.h"

int ledPin = 5;
int ledPin2 = 6;
int SensorPin = 2;
int SensorPin2 = 3;
int toiletLed = 9;
int toiletSensor = 8;
int val = 0;
int bath = 0;   // статус света в ванной
int bath2 = 0;   // статус света в ванной
int bathVal = 0;// мгновенное состояние
int bathVal2 = 0;// мгновенное состояние
int bathTimer = 600; //секунды
int curentBathTimer = 0;
int toilet = 0;
int toiletVal = 0;
int toiletTimer = 600;
int curentToiletT = 0;
int prog[] = {0,110,180,255}; // программы освещения ванной
int curentProg = 3;
int curentProg2 = 3;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(SensorPin, INPUT);
  pinMode(SensorPin2, INPUT);
  pinMode(toiletLed, OUTPUT);
  pinMode(toiletSensor, INPUT);
  pinMode(13, OUTPUT);
  timer_init_ISR_50Hz(TIMER_DEFAULT);
}
void loop() {
  analogWrite(ledPin, bathVal);
  analogWrite(ledPin2, bathVal2);
}

void timer_handle_interrupts(int timer) {
  if (digitalRead(SensorPin) || digitalRead(SensorPin2)){ //если движение в ванной
    bath = prog[curentProg]; //устанавливаем яркость в соотвествии выбранной программой 
    bath2 = prog[curentProg2]; 
    curentBathTimer = bathTimer * 50; //устанавливаем таймер
    //digitalWrite(13, !digitalRead(13));
  }
   else {
    if (curentBathTimer > 0) {--curentBathTimer;} else {bath = 0; bath2 = 0;} //уменьшаем таймер на 1
  }
   
    if (bathVal < bath) ++bathVal;
    if (bathVal > bath) --bathVal;
    if (bathVal2 < bath2) ++bathVal2;
    if (bathVal2 > bath2) --bathVal2;

  if (digitalRead(toiletSensor)) { // движение в туалете
    digitalWrite(toiletLed, LOW); 
    curentToiletT = toiletTimer * 50; //таймер туалета
  }
  else{
    if (curentToiletT > 0) {--curentToiletT;} else {digitalWrite(toiletLed, HIGH);}
  }
}
