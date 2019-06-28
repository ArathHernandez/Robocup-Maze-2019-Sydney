 #include <Arduino.h>
#include "SenseMap.h"

Ultrasonic front(28, 29);
Ultrasonic raight(30, 31);
Ultrasonic left(32, 33);
Ultrasonic back(35, 34);

SenseMap::SenseMap(){}

void SenseMap::setup()
{
  i2c_init(); 
  pinMode(37, OUTPUT);
  pinMode(38, OUTPUT);
  pinMode(39, OUTPUT);

    motors.escribirNumLCD(getDistanceOf(3));
    delay(300);
    motors.escribirNumLCD(getDistanceOf(2));
    delay(300);
    motors.escribirNumLCD(getDistanceOf(1));
    delay(300);
    motors.escribirNumLCD(getDistanceOf(4));
    delay(300);
    
  firstTemperature=(temperatureCelcius(mlxRight)+temperatureCelcius(mlxLeft))/2;
}

int SenseMap::getDistanceOf(uint8_t num)
{  
  if(num == 1)
    distance = left.read();
  else if(num == 2)
    distance = raight.read();
  else if(num == 3)
    distance = front.read();
  else if(num == 4)
    distance = back.read();
  
  return distance;
}

float SenseMap::temperatureCelcius(int mlx) 
{
  int dev = mlx;
  int data_low = 0;
  int data_high = 0;
  int pec = 0;
  
  i2c_start_wait(dev+I2C_WRITE);
  i2c_write(0x07);
  
  i2c_rep_start(dev+I2C_READ);
  data_low = i2c_readAck();
  data_high = i2c_readAck();
  pec = i2c_readNak();
  i2c_stop();
  
  double tempFactor = 0.02;
  double tempData = 0x0000;
  int frac;
  
  tempData = (double)(((data_high & 0x007F) << 8) + data_low);
  tempData = (tempData * tempFactor)-0.01;
  float celcius = tempData - 273.15;
  
  return celcius;
}

void SenseMap::checkDistances()
{
motors.setBase(motors.velInicial);

int d1 = this -> getDistanceOf(3);
int pp;
if (motors.bumperControl)
pp=18;
else
pp=14;

  if(d1 >= 7 && d1 <= pp)
  {  
    unsigned long tempoo = millis();
    
    while(this -> getDistanceOf(3) >= 7.3)
    {
      motors.avanzar(motors.de,30,30,motors.bD);
      
      if(millis()>(tempoo+300))
        break;
    }
    
  motors.detenerse();
  }
  else if(d1 <= 5 || d1>350)
  {
    unsigned long ter = millis();
    
    while(this -> getDistanceOf(3) <= 5 || getDistanceOf(3)>350)
    {
      motors.atrasPID(motors.de);
      if(millis()>(ter+200))
      break;
    }
    motors.detenerse();
  }
  
  int disss = this -> getDistanceOf(3);
  
  if(disss >= 27 && disss <= 42) //36
  {
    unsigned long terr = millis();
    
    if(disss >= 31 && disss <= 38)
    {}
    else if(disss > 38)
    {
      while(this -> getDistanceOf(3) > 38)
      {
        motors.avanzar(motors.de,30,30,motors.bD);
        if(millis() > (terr + 200))
          break;
      }
      
     motors.detenerse();
    }
    else if(disss < 31)
    {
      while(this -> getDistanceOf(3) < 31)
       {
          motors.atrasPID(motors.de);
          if(millis() > (terr+200))
           break;
       }
       
     motors.detenerse();
    }
    
  }
}

void SenseMap::acomodo(double dEI,double dAI)
{


  if(abs(dEI-dAI)<20)
  dAI=300;
  
  char pos = dEI<dAI?'E':'A';
  double m = dEI<=dAI?dEI:dAI;
  
  if(m>80)
  return;
  
unsigned long nlp = millis();

int k = teMamaste(m,pos);
  
    if(k!=0){
    motors.setBase(motors.velInicial);

    while(k!=0)
    {
      k=teMamaste(m,pos);
      
      if(k==1)
      motors.avanzar(motors.de,30,30,motors.bD);
      else if(k==2)
      {
   motors.detenerse();
   return;
      }

      if(millis()>(nlp+650))
      {
   motors.detenerse();
   return;
      }
    }
 motors.detenerse();
   }
}
int SenseMap::teMamaste(double disI, char pos)
{
  double dActual;
  if(pos=='E')
  {
    dActual=this -> getDistanceOf(3);
    
    if(dActual<(disI-33))
    return 1;
    else if(dActual>(disI-27))
    return 2;
    else
    return 0;
  }
  else if (pos == 'A')
  {
    dActual=this -> getDistanceOf(4);

    
    if(dActual<(disI+27))
    return 1;
    else if(dActual>(disI+33))
    return 2;
    else 
    return 0;
  }
}

void SenseMap::blinkLeds()
{
  for(int i = 0; i < 5; i++)
  {
    digitalWrite(37, HIGH);
    delay(500);
    digitalWrite(37, LOW);
    digitalWrite(39, HIGH);
    delay(500);
    digitalWrite(39, LOW);
  }
}
