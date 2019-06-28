#ifndef SenseMap_h
#define SenseMap_h

#include <Arduino.h>
#include <i2cmaster.h>
#include <LiquidCrystal_I2C.h>
#include <Ultrasonic.h>
#include "Control.h"

class SenseMap
{
  public:
  
    SenseMap();
    Control motors;
    
    void setup();
    int getDistanceOf(uint8_t num);
    float temperatureCelcius(int address);
    float firstTemperature;
    void checkDistances();
    int teMamaste(double,char);
    void acomodo(double,double);
    void blinkLeds();
    
    int mlxRight = 0x55<<1;    
    int mlxLeft = 0x2A<<1; 
    
   private:
   
    int distance;    
    int uS;
};

#endif
