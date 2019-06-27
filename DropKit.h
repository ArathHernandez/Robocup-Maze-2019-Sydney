#ifndef DropKit_h
#define DropKit_h

#include <Arduino.h>
#include <Servo.h>

class DropKit
{
  public:
  
    DropKit();
    Servo dispenser;
    
    void setup();
    void dropOneKitRight();
    void dropOneKitLeft();
    void dropTwoKitsRight();
    void dropTwoKitsLeft();
    
   private:
};

#endif

