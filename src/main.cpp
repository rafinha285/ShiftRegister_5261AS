#include <Arduino.h>
#include "C_5261ASS.h"
// #include <TimerOne.h>

#define UnitPin 30
#define DecimalPin 28
#define SerialOPin 22
#define LatchClock 24
#define SerialClock 26
#define ResetPin 5

// void sendSerial(int i);
C_5261AS* ci;

unsigned long lastUpdate = 0;
int currentChar = 0;

void setup(){
    Serial.begin(9600);
    delay(1000);  // espera a inicialização da serial
    Serial.println("Iniciando...");
    ci = new C_5261AS(DecimalPin, UnitPin, SerialOPin, SerialClock, LatchClock,5);
    // ci->beginTimer(5); // 5ms
}

void loop(){
    ci->sendCharacter(currentChar++, currentChar % 4, currentChar % 2);
    if (currentChar > 255) currentChar = 0;
    delay(500); 
}