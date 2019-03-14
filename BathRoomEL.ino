#include "timer-api.h"

int ledPin = 5;
int SensorPin = 2;
int val = 0;
int bath = 0;   // статус света в ванной
int bathVal = 0;// мгновенное состояние
int bathTimer = 5; //секунды
int curentBathTimer = 0;
int prog[] = {0,90,160,255}; // программы освещения
int curentProg = 3;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(SensorPin, INPUT);
  pinMode(13, OUTPUT);
  timer_init_ISR_50Hz(TIMER_DEFAULT);
}
void loop() {
  analogWrite(ledPin, bathVal);
}

void timer_handle_interrupts(int timer) {
  if (digitalRead(SensorPin)){
    bath = prog[curentProg];
    curentBathTimer = bathTimer * 50;
  }
   else {
    if (curentBathTimer > 0) {--curentBathTimer;} else {bath = 0;}
  }
   
    if (bathVal < bath) bathVal += 2;
    if (bathVal > bath) --bathVal;
    //digitalWrite(13, !digitalRead(13));
}
