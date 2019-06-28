#ifndef Bit_h
#define Bit_h

#include <Arduino.h>

class Bit {
  public:
  
    Bit();
    
    bool up();
    bool right();
    bool down();
    bool left();
    bool victim();
    bool blackTile();
    bool checkpoint();
    bool visited();
    uint8_t flo0r();
    bool downRamp();
    bool pending();
    bool exist();
    bool upRamp();
    bool bumper();

    void up(const bool &b, Bit *theTop);
    void right(const bool &b, Bit *theRight);
    void down(const bool &b, Bit *theDown);
    void left(const bool &b, Bit *theLeft);
    void victim(const bool &b);
    void blackTile(const bool &b);
    void checkpoint(const bool &b);
    void visited(const bool &b);
    void flo0r(const int &i);
    void downRamp(const bool &b);
    void exist(const bool &b);
    void upRamp(const bool &b);
    void pending(const bool &b);
    void bumper(const bool &b);

    char getInf1();
    char getInf2();
    void setInf1(char info);
    void setInf2(char info);


  private:
  
    char inf1, inf2;
};

#endif
