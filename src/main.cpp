#include <Arduino.h>
#include "C_5261ASS.h"

#define UnitPin 2
#define DecimalPin 3
#define SerialOPin 4
#define OutputEnable 5
#define LatchClock 6
#define SerialClock 7
#define LatchReset 8

void setup(){
  Serial.begin(115200);
  delay(1000);
  static C_5261AS shiftRe(DecimalPin,UnitPin,SerialOPin,OutputEnable,SerialClock,LatchClock, LatchReset);
  shiftRe.sendCharacter("FF");
}

void loop(){

}