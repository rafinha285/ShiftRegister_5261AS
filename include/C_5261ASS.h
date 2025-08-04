#ifndef C_5261ASS_H
#define C_5261ASS_H

class C_5261AS {
    public:
        C_5261AS(int d, int u, int ser, int shClk, int lcClk);
        C_5261AS(int d, int u, int ser, int shClk, int lcClk, int time);
        void sendCharacter(String input, bool dpDecimal, bool dpUnidade);
        void sendCharacter(int input, bool dpDecimal, bool dpUnidade);
        
        void interruptUpdate();
        
        void setSerialPin(int serialPin);
        void setShiftClockPin(int shiftClockPin);
        void setLatchClockPin(int latchClockPin);
        void setTime(int time);
        

    
    private:
        int time;
        int DPin;
        int UPin;
        int serialPin;
        int shiftClock;
        int latchClock;
        byte valorDecimal;
        byte valorUnidade;
        unsigned long lastUpdate = 0;
        void beginTimer(int time);
        bool showingDecimal = true;
        void printPins() const;
        void initPins() const;
        void changeDisplay(bool d);
        void sendToDisplay(int dezenaHex, int unidadeHex, bool dpDecimal, bool dpUnidade);
};

#endif C_5261ASS_H