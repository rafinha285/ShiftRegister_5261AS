#ifndef C_5261ASS_H
#define C_5261ASS_H

class C_5261AS {
public:

    C_5261AS(int d, int u, int ser, int shClk, int lcClk);
    void sendCharacter(String input, bool dpDecimal, bool dpUnidade);
    void sendCharacter(int input, bool dpDecimal, bool dpUnidade);
    void interruptUpdate();
    void beginTimer(int time);

private:
    bool active;
    int DPin;
    int UPin;
    int SerialPin;
    int shiftClock;
    int latchClock;
    byte valorDecimal;
    byte valorUnidade;
    unsigned long lastUpdate = 0;
    bool showingDecimal = true;
    void printPins() const;
    void initPins() const;
    void changeDisplay(bool d);
    void sendToDisplay(int dezenaHex, int unidadeHex, bool dpDecimal, bool dpUnidade);
};

#endif