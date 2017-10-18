#include <string.h> //Библиотека для работ со строками
#include <stdio.h> //Библиотека для преобразования

//LED defines
#define PLAYER_1_LED 18
#define PLAYER_2_LED 19
#define PLAYER_3_LED 20
#define PLAYER_4_LED 21
#define MAIN_LED

//Button deffines
#define PLAYER_1_BTN 14
#define PLAYER_2_BTN 15
#define PLAYER_3_BTN 16
#define PLAYER_4_BTN 17

//my defines
#define NORMAL_STATE 0
#define SD_INIT_FAIL 1
#define ANSWER_TIME_OUT 20000 //Время на ответ

uint8_t main_state = NORMAL_STATE;
uint32_t players_time_stamps[3];
butt

void statusProcces(){
  
}

void BTNGetTimeStamps(){ //cheching if button pressed and record time stamps
 
  
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
}

void loop() {
  statusProcces();
  BTNWorks();
  LEDWorks();
}
