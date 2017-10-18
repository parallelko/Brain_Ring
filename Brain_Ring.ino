#include <string.h> //Библиотека для работ со строками
#include <stdio.h> //Библиотека для преобразования
#include <MsTimer2.h> //Библиотека для работы с прерыванием по таймеру

//LED defines
#define PLAYER_1_LED 18
#define PLAYER_2_LED 19
#define PLAYER_3_LED 20
#define PLAYER_4_LED 21
#define MAIN_LED 33

//Button deffines
#define PLAYER_1_BTN 14
#define PLAYER_2_BTN 15
#define PLAYER_3_BTN 16
#define PLAYER_4_BTN 17
#define PLAYER_5_BTN 18
#define SKIP_BTN 19
#define NEXT_BTN 20

//my defines
#define NORMAL_STATE 0
#define PREPARE 1
#define WAIT_FOR_ANSWER 2
#define ANSWER 3
#define UNPRESS 0
#define PRESS 1
#define FAILED 2
#define ANSWER_TIME_OUT 20000 //Время на ответ
#define BTN_PROCCESS_FREQ 20
#define MAX_PLAYERS 5
#define BIG 600000

byte BTNPins[MAX_PLAYERS] = {PLAYER_1_BTN,PLAYER_2_BTN,PLAYER_3_BTN,PLAYER_4_BTN,PLAYER_5_BTN};
uint8_t main_state = PREPARE;
uint32_t buttons_time_stamps[MAX_PLAYERS];
uint32_t PASSED_time_stamps[MAX_PLAYERS];
uint32_t startMillis;
uint8_t buttonsStates[MAX_PLAYERS];
uint8_t pl_num;

void BTNcheck() { //Проверка нажатий на кнопку после заданного вопроса
  byte i;
  switch (main_state){
    case ANSWER :
    case WAIT_FOR_ANSWER: {
      for (i = 0; i < MAX_PLAYERS; i++) {
        if (buttonsStates[i] != FAILED && buttonsStates[i] != PRESS ) { //обрабатываем только тех кто не нажал
          if ((buttons_time_stamps[i]-startMillis)> 0) {
            PASSED_time_stamps[i] = buttons_time_stamps[i]-startMillis;
            buttonsStates[i] = PRESS;
          }
        }
      }
      break;
    }
  }
}

uint8_t getNext(){
  uint32_t minTime = BIG;
  uint8_t j = 0;
     for (byte k = 0; k < MAX_PLAYERS; k++){ //Проход по кнопкам всех игроков
      if (buttonsStates[k] != FAILED && buttonsStates[k] == PRESS ) {//Обрабатываем только тех кто нажал и исключаем из обработки ошибившихся 
         if (PASSED_time_stamps[k] < minTime) {
            minTime = PASSED_time_stamps[k]; //Запоминаем минимальное время
            j = k; //Запоминаем номер игрока
         }
      }
     }
    return j;
}
        
void statusProcces(){
  switch (main_state){
    case NORMAL_STATE : {
      if (digitalRead(SKIP_BTN)== HIGH) {
        main_state = WAIT_FOR_ANSWER;
        startMillis = millis();
        break;
      }
      break;
    }
    case PREPARE : {
      for (byte i = 0; i < MAX_PLAYERS; i++){
        buttonsStates[i] = UNPRESS;
        PASSED_time_stamps[i] = 0;
      }
      pl_num = 0;
      main_state = NORMAL_STATE;
      break;
    }
    case ANSWER :{
      if (digitalRead(SKIP_BTN)== HIGH) {
        main_state = PREPARE;
        break;
      }
      if (digitalRead(NEXT_BTN) == HIGH) {
        buttonsStates[pl_num]= FAILED;
        main_state = WAIT_FOR_ANSWER;
        break; 
      }
      break;
     }
    case WAIT_FOR_ANSWER : {
      pl_num = getNext();
      if (pl_num != 0){
        main_state = ANSWER;
      }
      break;
    }
  }
}

void BTNProccess(){ //Proccess buttons states, and get TimeStamps
 for (byte i = 0; i < MAX_PLAYERS; i++){
  if (digitalRead(BTNPins[i]) == HIGH){
    buttons_time_stamps[i] = millis();
  }
 }
}

void LEDWorks(){
  
}

void LED_INIT() {
 pinMode(PLAYER_1_LED, OUTPUT);
 pinMode(PLAYER_2_LED, OUTPUT);
 pinMode(PLAYER_3_LED, OUTPUT);
 pinMode(PLAYER_4_LED, OUTPUT);  
}

void BTN_INIT() {
  pinMode(PLAYER_1_BTN , INPUT);
  pinMode(PLAYER_2_BTN , INPUT);
  pinMode(PLAYER_3_BTN , INPUT);
  pinMode(PLAYER_4_BTN , INPUT);
}

void setup() {
    LED_INIT();
    BTN_INIT();
    MsTimer2::set(BTN_PROCCESS_FREQ, BTNProccess);
    MsTimer2::start();
}

void loop() {
  BTNcheck();
  statusProcces();
  LEDWorks();
}
