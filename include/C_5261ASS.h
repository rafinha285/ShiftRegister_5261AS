#ifndef C_5261ASS_H
#define C_5261ASS_H

class C_5261AS {
public:
    bool active;
    int DPin;
    int UPin;
    int SerialPin;
    int outputEnable;
    int shiftClock;
    int latchClock;
    int reset;

    C_5261AS(int d, int u, int ser, int oe, int shClk, int lcClk, int rst);
    void sendCharacter(String input);

private:
    void printPins();
    void initPins();
    void changeDisplay(bool d);
    int getPatternFromHex(uint8_t hex);
    void sendToDisplay(int dezenaHex, int unidadeHex);
};

#endif