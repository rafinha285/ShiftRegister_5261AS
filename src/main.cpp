#include <Arduino.h>

#define UnitPin 2
#define DecimalPin 3
#define SerialOPin 4
#define OutputEnable 5
#define LatchClock 6
#define SerialClock 7
#define LatchReset 8

class C_5261AS{
  const int digits [17] = { 0x11,
                            0x9F,
                            0xCE,
                            0x47,
                            0xCD,
                            0xDD,
                            0xC2,
                            0xDF,
                            0xCF,
                            0xDB,
                            0xD7,
                            0x5D,
                            0x99,
                            0x5E,
                            0x9D,
                            0x95
};
const int DP = 0b00100000;
  public:
    //false = DPin; true = UPin
    bool active;
    //para ativar os UPin e DPin é active LOW
    int DPin;
    int UPin;
    //saida de dados em sequencia
    int SerialPin;
    int outputEnable;
    int shiftClock;
    int latchClock;
    int reset;

    C_5261AS(int d, int u, int ser, int oe, int shClk, int lcClk, int rst){
      active = false;
      DPin = d;
      UPin = u,
      SerialPin = ser;
      outputEnable = oe;
      shiftClock = shClk;
      latchClock = lcClk;
      reset = rst;  
      printPins();
      initPins();
    }

  private:
    void printPins(){
      Serial.print("active: ");
      Serial.println(active ? "DPin": "UPin");
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

    void initPins(){
      pinMode(DPin, OUTPUT);
      pinMode(UPin, OUTPUT);
      pinMode(SerialPin, OUTPUT);
      pinMode(outputEnable, OUTPUT);
      pinMode(shiftClock, OUTPUT);
      pinMode(latchClock, OUTPUT);
      pinMode(reset, OUTPUT);

      digitalWrite(DPin, HIGH);
      digitalWrite(UPin, HIGH);
      // Inicializa os pinos em estado LOW por segurança
      digitalWrite(SerialPin, LOW);
      digitalWrite(outputEnable, LOW);
      digitalWrite(shiftClock, LOW);
      digitalWrite(latchClock, LOW);
      digitalWrite(reset, LOW);
    }

    void changeDisplay(){
      digitalWrite(DPin, active ? HIGH : LOW);
      digitalWrite(UPin, active ? LOW : HIGH);
      active = false;
    }

};

void setup(){
  Serial.begin(9600);
  C_5261AS shiftRe(DecimalPin,UnitPin,SerialOPin,OutputEnable,SerialClock,LatchClock, LatchReset);
}

void loop(){

}