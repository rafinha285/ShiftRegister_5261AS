#include <Arduino.h>
#include "C_5261ASS.h"

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
    ci = new C_5261AS(DecimalPin, UnitPin, SerialOPin, SerialClock, LatchClock);
    // ci.sendCharacter("FF");
    ci->sendCharacter(0xef, false, false);
}

void loop(){
    ci->updateDisplay(); // Sempre mantém o display funcionando
    unsigned long now = millis();
    if (now - lastUpdate >= 200) {  // A cada 500ms
        lastUpdate = now;
        ci->sendCharacter(currentChar++, currentChar % 4, currentChar % 2);
        if (currentChar > 255) currentChar = 0;
    }
    // ci->sendCharacter(currentChar++);
    // if (currentChar > 255) currentChar = 0;
    // delay(500);
}