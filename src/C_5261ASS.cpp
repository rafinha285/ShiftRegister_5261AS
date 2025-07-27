#include <Arduino.h>
#include "C_5261ASS.h"

const int digits[16] = {
    0xDB ,0x11, 0x9F, 0xCE, 0x47,
    0xCD, 0xDD, 0xC2, 0xDF, 0xCF,
    0xD7, 0x5D, 0x99, 0x5E, 0x9D,
    0x95
};

const int DP = 0b00100000;

C_5261AS::C_5261AS(int d, int u, int ser, int oe, int shClk, int lcClk, int rst) {
    active = false;
    DPin = d;
    UPin = u;
    SerialPin = ser;
    outputEnable = oe;
    shiftClock = shClk;
    latchClock = lcClk;
    reset = rst;
    printPins();
    initPins();
}

void C_5261AS::printPins() {
    Serial.print("active: ");
    Serial.println(active ? "DPin" : "UPin");
    Serial.print("UnitPin: ");
    Serial.println(UPin);
    Serial.print("DecimalPin: ");
    Serial.println(DPin);
    Serial.print("Serial Output: ");
    Serial.println(SerialPin);
    Serial.print("OutputEnable: ");
    Serial.println(outputEnable);
    Serial.print("Shift Clock: ");
    Serial.println(shiftClock);
    Serial.print("Latch Clock: ");
    Serial.println(latchClock);
    Serial.print("Reset: ");
    Serial.println(reset);
}

void C_5261AS::initPins() {
    pinMode(DPin, OUTPUT);
    pinMode(UPin, OUTPUT);
    pinMode(SerialPin, OUTPUT);
    pinMode(outputEnable, OUTPUT);
    pinMode(shiftClock, OUTPUT);
    pinMode(latchClock, OUTPUT);
    pinMode(reset, OUTPUT);

    digitalWrite(DPin, HIGH);
    digitalWrite(UPin, HIGH);
    digitalWrite(SerialPin, LOW);
    digitalWrite(outputEnable, LOW);
    digitalWrite(shiftClock, LOW);
    digitalWrite(latchClock, LOW);
    digitalWrite(reset, LOW);
}

void C_5261AS::changeDisplay(bool d) {
    active = d;
    digitalWrite(DPin, d);
    digitalWrite(UPin, !d);
    // digitalWrite(DPin, active ? HIGH : LOW);
    // digitalWrite(UPin, active ? LOW : HIGH);
    // active = false;
}

void C_5261AS::sendCharacter(String input){
    input.trim();

    int num = -1;

    if(input.length() <= 2 && isDigit(input[0])){
        num = input.toInt();
    }

    if(num < 0 || num>99){
        num = strtol(input.c_str(), NULL, 16);
    }



    if(num >= 0 && num<= 255){
        int dezena = num / 16;
        int unidade = num % 16;

        Serial.print("Sending: "); Serial.print(dezena, HEX); Serial.print(" "); Serial.println(unidade, HEX);
        sendToDisplay(dezena, unidade);
    }else{
        Serial.println("Entrada inválida");
    }
}

void C_5261AS::sendToDisplay(int dezenaHex, int unidadeHex){
    if (dezenaHex < 0 || dezenaHex > 15 || unidadeHex < 0 || unidadeHex > 15) return;

    byte valorDecimal = digits[dezenaHex];
    byte valorUnidade = digits[unidadeHex];

    digitalWrite(latchClock, LOW);
    shiftOut(SerialPin, shiftClock, MSBFIRST, valorDecimal);
    changeDisplay(true);
    digitalWrite(latchClock, HIGH);

    digitalWrite(latchClock, LOW);
    shiftOut(SerialPin, shiftClock, MSBFIRST, valorUnidade);
    changeDisplay(false);
    digitalWrite(latchClock, HIGH);
}


