#ifndef Control_h
#define Control_h

#include "arduino.h"
#include <Wire.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <LiquidCrystal_I2C.h>
#include <VL53L0X.h>
#include <Adafruit_TCS34725.h>


extern "C" 
{
   #include "utility/twi.h"  
}

#define BNO055_SAMPLERATE_DELAY_MS 10
#define TCAADDR 0x70


class Control {

  public:
  
      Control();
      Adafruit_BNO055 bno;
      void avanzar(double,double,double,int&);
      void tcaselect(int);
      void adelante(int,int);
      void peid();
      void giroDer(double);
      void giroIzq(double);  
      void dondeGirar(double);
      void dondeGirar1(double,int);
      void giro(double);
      void checa(double);
      void giroD(int);
      void giroI(int);
      void actualizaSetPoint(double);
      void atras();
      void atras1();
      void atrasSN();
      int rampa(double);
      double y();
      bool bumper(uint8_t&);
      void atrasPID(double);
      void setBase(double);
      void detenerse();  //chido
      void setup();    //chido
      bool desalineao(double,double);
      void choqueIzq(double,int);
      void choqueDer(double,int);
      bool cuadroNegro();
      int tofDE();
      int tofDA();
      int tofIE();
      int tofIA();
      int orientationStatus();
      void moveAdelante();
      void moveAdelanteFast();
      void moveAtras();
      void setPointTFO(double, bool);
      void escribirLCDabajo(String);
      void escribirLCD(String, String);
      void escribirNumLCD(int);
      void escribirLetraLCD(char);
      void checar();
      void actualizaSetPointY();
  
      const int motorIzqAde1  = 9;  
      const int motorIzqAde2  = 8;  
      const int motorIzqAtras1  = 10;
      const int motorIzqAtras2  = 11;
      const int motorDerAde1  = 5;
      const int motorDerAde2  = 4;
      const int motorDerAtras1  = 7;
      const int motorDerAtras2  = 6;
      void printLoc(int,int,int);
      bool condRampa(bool);
      
      int pin1 = 23; //derecha enmedio
      int pin2 = 25; //derecha esquina
      int pin3 = 27; //izquierda enmedio
      int pin4 = 22; //derecha orilla
      int pin5 = 26; //izq orilla
      int pin6 = 24; //izq esquina
  
      double getSetpoint(double);
      double getAnguloActual();

      int tic1=1266;//660
      int tic=tic1;
      int bD=0;
      double de = 0;
      long rightCount = 0;
      int girosX = 0;
      bool bumperControl = false;
      bool bT = false;
      double velInicial=152;
};


#endif
