#include <Arduino.h>
#include "C_5261ASS.h"
#include <TimerOne.h>

C_5261AS* global_instance = nullptr;

void timerInterruptHandler() {
    if (global_instance != nullptr) {
        global_instance->interruptUpdate();
    }
}
void C_5261AS::beginTimer(int time) {
    global_instance = this;
    Timer1.initialize(time * 1000);  // 5ms -> 100Hz multiplex
    Timer1.attachInterrupt(timerInterruptHandler);
}

const uint8_t digits[16] = {
    //G F E D C B A DP
    0b01111110, // 0
    0b00001100, // 1
    0b10110110, // 2
    0b10011110, // 3
    0b11001100, // 4
    0b11011010, // 5
    0b11111010, // 6
    0b00001110, // 7
    0b11111110, // 8
    0b11011110, // 9
    0b11101110, // A
    0b11111000, // B
    0b01110010, // C
    0b10111100, // D
    0b11110010, // E
    0b11100010  // F
};

C_5261AS::C_5261AS(int d, int u, int ser, int shClk, int lcClk) {
    active = false;
    DPin = d;
    UPin = u;
    SerialPin = ser;
    shiftClock = shClk;
    latchClock = lcClk;
    valorDecimal = 0;
    valorUnidade = 0;
    initPins();
    printPins();
}

void C_5261AS::printPins() const {
    Serial.print("UnitPin: ");
    Serial.println(UPin);
    Serial.print("DecimalPin: ");
    Serial.println(DPin);
    Serial.print("Serial Output: ");
    Serial.println(SerialPin);
    Serial.print("Shift Clock: ");
    Serial.println(shiftClock);
    Serial.print("Latch Clock: ");
    Serial.println(latchClock);
}

void C_5261AS::initPins() const {
    pinMode(DPin, OUTPUT);
    pinMode(UPin, OUTPUT);
    pinMode(SerialPin, OUTPUT);
    pinMode(shiftClock, OUTPUT);
    pinMode(latchClock, OUTPUT);

    digitalWrite(DPin, HIGH);
    digitalWrite(UPin, HIGH);
    digitalWrite(SerialPin, LOW);
    digitalWrite(shiftClock, LOW);
    digitalWrite(latchClock, LOW);
}

void C_5261AS::changeDisplay(const bool d) {
    active = d;
    // Serial.println(d);
    // Serial.println(!d);
    digitalWrite(DPin, d);
    digitalWrite(UPin, !d);
    // digitalWrite(DPin, active ? HIGH : LOW);
    // digitalWrite(UPin, active ? LOW : HIGH);
    // active = false;
}

void C_5261AS::sendCharacter(String input, bool dpDecimal, bool dpUnidade){
    input.trim();

    // Aceita entrada hexadecimal sempre
    int num = strtol(input.c_str(), NULL, 16);

    if (num >= 0 && num <= 255) {
        int dezena = num / 16;
        int unidade = num % 16;

        sendToDisplay(dezena, unidade, dpDecimal, dpUnidade);
    } else {
        Serial.println("Entrada inválida");
    }
}

void C_5261AS::sendCharacter(int input, bool dpDecimal, bool dpUnidade) {
    if (input >= 0 && input <= 255) {
        int dezena = input / 16;
        int unidade = input % 16;

        sendToDisplay(dezena, unidade, dpDecimal, dpUnidade);
    } else {
        Serial.println("Entrada inválida");
    }
}

void C_5261AS::sendToDisplay(int dezenaHex, int unidadeHex, bool dpDecimal, bool dpUnidade){
    if (dezenaHex < 0 || dezenaHex > 15 || unidadeHex < 0 || unidadeHex > 15) return;

    valorDecimal = digits[dezenaHex];
    valorUnidade = digits[unidadeHex];
    if (dpDecimal) valorDecimal |= 0b00000001;
    if (dpUnidade) valorUnidade |= 0b00000001;

}

void C_5261AS::interruptUpdate() {
    digitalWrite(latchClock, LOW);
    if (showingDecimal) {
        shiftOut(SerialPin, shiftClock, MSBFIRST, valorDecimal);
        changeDisplay(true);
    } else {
        shiftOut(SerialPin, shiftClock, MSBFIRST, valorUnidade);
        changeDisplay(false);
    }
    digitalWrite(latchClock, HIGH);
    showingDecimal = !showingDecimal;
}


