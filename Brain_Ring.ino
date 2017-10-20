#include <string.h> 
#include <stdio.h> 
#include <MsTimer2.h> 
#include <SPI.h> 
#include <Ethernet.h>

//LED defines
#define MAIN_LED 33

//Button deffines
#define PLAYER_1_BTN 9
#define PLAYER_2_BTN 8
#define PLAYER_3_BTN 7
#define PLAYER_4_BTN 
#define PLAYER_5_BTN 
#define SKIP_BTN 6
#define NEXT_BTN 5

//my defines
#define NORMAL_STATE 0
#define PREPARE 1
#define WAIT_FOR_ANSWER 2
#define ANSWER 3
#define UNPRESS 0
#define PRESS 1
#define FAILED 2
#define ANSWER_TIME_OUT 20000
#define BTN_PROCCESS_FREQ 20
#define MAX_PLAYERS 3
#define BIG 60000000

byte BTNPins[MAX_PLAYERS] = {PLAYER_1_BTN,PLAYER_2_BTN,PLAYER_3_BTN};//,PLAYER_4_BTN,PLAYER_5_BTN};
uint8_t main_state = PREPARE;
uint32_t buttons_time_stamps[MAX_PLAYERS];
uint32_t PASSED_time_stamps[MAX_PLAYERS];
uint32_t startMillis;
uint8_t buttonsStates[MAX_PLAYERS];
uint8_t pl_num;

void BTNcheck() { 
  byte i;
  switch (main_state){
    case ANSWER :
    case WAIT_FOR_ANSWER: {
      for (i = 0; i < MAX_PLAYERS; i++) {
        if (buttonsStates[i] != FAILED && buttonsStates[i] != PRESS ) {
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
     for (byte k = 0; k < MAX_PLAYERS; k++){ 
      if (buttonsStates[k] != FAILED && buttonsStates[k] == PRESS ) {
         if (PASSED_time_stamps[k] < minTime) {
            minTime = PASSED_time_stamps[k]; 
            j = k; 
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

void BTN_INIT() {
  pinMode(PLAYER_1_BTN , INPUT);
  pinMode(PLAYER_2_BTN , INPUT);
  pinMode(PLAYER_3_BTN , INPUT);
  //pinMode(PLAYER_4_BTN , INPUT);
  pinMode(SKIP_BTN, INPUT);
  pinMode(NEXT_BTN, INPUT);
}

void setup() {
    BTN_INIT();
    MsTimer2::set(BTN_PROCCESS_FREQ, BTNProccess);
    MsTimer2::start();
    serverINIT();
}

void loop() {
  BTNcheck();
  statusProcces();
  //LEDWorks();
  serverWorks();
}

