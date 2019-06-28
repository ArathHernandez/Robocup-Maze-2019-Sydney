#include <Arduino.h>
#include "Algorithm.h"

SoftwareSerial cam(50, 51);
  
Algorithm::Algorithm(){

}

bool v = true;
void Algorithm::setup()
{
  cam.begin(115200);

}

bool Algorithm::heatVictim()
{
    if(sensors.temperatureCelcius(sensors.mlxLeft) > (sensors.firstTemperature + 10))
      {
        sensors.motors.detenerse();
        sensors.blinkLeds();
        robot.dispenser.dropOneKitLeft();
        return true;
      }
      if(sensors.temperatureCelcius(sensors.mlxRight) > (sensors.firstTemperature + 10))
      {
        sensors.motors.detenerse();
        sensors.blinkLeds();
        robot.dispenser.dropOneKitRight();
        return true;
      }

return false;
  
}

bool Algorithm::visualVictim()
{

  inByte =  '0';
  bool done = false;

    cam.listen();
    
    while (cam.available() > 0) {
    int dI = sensors.getDistanceOf(1);
    int dD = sensors.getDistanceOf(2);
    inByte = cam.read();

    while(inByte == '1' || inByte == 'A')
    {
     inByte= cam.read();
     sensors.motors.detenerse();
     sensors.motors.escribirLCD("BULTO", "BULTO");
     done=true;
    }
    
    if(inByte == '7' && dI < 21&& dI!=0 && done){
    sensors.motors.detenerse();
    sensors.motors.escribirLCD("LETRA S", "IZQUIERDA");
    sensors.blinkLeds();;
    return true;}
    else if(inByte == '8' && dI < 21 && dI!=0 && done){
    sensors.motors.detenerse();
    sensors.motors.escribirLCD("LETRA U", "IZQUIERDA");
    sensors.blinkLeds();
    return true;}
    else if(inByte == '6' && dI< 21 && dI!=0 && done){
    sensors.motors.detenerse();
    sensors.motors.escribirLCD("LETRA H", "IZQUIERDA");
    sensors.blinkLeds();
    return true;}
    /*else if(inByte == '5' && sensors.getDistanceOf(2) < 21){
    sensors.motors.detenerse();
    sensors.motors.escribirLCD("KIT", "DERECHA");
    sensors.blinkLeds();;
    return true;}
    else if(inByte == '9' && sensors.getDistanceOf(1) < 21){
    sensors.motors.detenerse();
    sensors.motors.escribirLCD("KIT", "IZQUIERDA");
    sensors.blinkLeds();;
    return true;}*/
    else if(inByte == '4' && dD < 21 && dD!=0 && done){
    sensors.motors.detenerse();
    sensors.motors.escribirLCD("LETRA U", "DERECHA");
    sensors.blinkLeds();
    return true;}
    else if(inByte == '3' && dD < 21 && dD!=0 && done){
    sensors.motors.detenerse();
    sensors.motors.escribirLCD("LETRA S", "DERECHA");
    sensors.blinkLeds();
    return true;}
    else if(inByte == '2' && dD < 21 && dD!=0 && done){
    sensors.motors.detenerse();
    sensors.motors.escribirLCD("LETRA H", "DERECHA");
    sensors.blinkLeds();;
    return true;}
    }

    return false;
}
bool Algorithm::visualVictim1()
{

  inByte =  '0';
  bool done = false;

    cam.listen();
    while (cam.available() > 0) {
    int dI = sensors.getDistanceOf(1);
    int dD = sensors.getDistanceOf(2);
    inByte = cam.read();
    if(inByte == '7' && dI < 21&& dI!=0 && done){
    sensors.motors.detenerse();
    sensors.motors.escribirLCD("LETRA S", "IZQUIERDA");
    sensors.blinkLeds();;
    return true;}
    else if(inByte == '8' && dI < 21 && dI!=0 && done){
    sensors.motors.detenerse();
    sensors.motors.escribirLCD("LETRA U", "IZQUIERDA");
    sensors.blinkLeds();
    return true;}
    else if(inByte == '6' && dI< 21 && dI!=0 && done){
    sensors.motors.detenerse();
    sensors.motors.escribirLCD("LETRA H", "IZQUIERDA");
    sensors.blinkLeds();
    return true;}
    /*else if(inByte == '5' && sensors.getDistanceOf(2) < 21){
    sensors.motors.detenerse();
    sensors.motors.escribirLCD("KIT", "DERECHA");
    sensors.blinkLeds();;
    return true;}
    else if(inByte == '9' && sensors.getDistanceOf(1) < 21){
    sensors.motors.detenerse();
    sensors.motors.escribirLCD("KIT", "IZQUIERDA");
    sensors.blinkLeds();;
    return true;}*/
    else if(inByte == '4' && dD < 21 && dD!=0 && done){
    sensors.motors.detenerse();
    sensors.motors.escribirLCD("LETRA U", "DERECHA");
    sensors.blinkLeds();
    return true;}
    else if(inByte == '3' && dD < 21 && dD!=0 && done){
    sensors.motors.detenerse();
    sensors.motors.escribirLCD("LETRA S", "DERECHA");
    sensors.blinkLeds();
    return true;}
    else if(inByte == '2' && dD < 21 && dD!=0 && done){
    sensors.motors.detenerse();
    sensors.motors.escribirLCD("LETRA H", "DERECHA");
    sensors.blinkLeds();;
    return true;}
    else if(inByte == '1' && dD < 21 && dD!=0 && !done){
    sensors.motors.detenerse();
    sensors.motors.escribirLCD("BULTO", "BULTO");
    done = true;}
    else if(inByte == 'A' && dI < 21 && dI!=0 && !done){
    sensors.motors.detenerse();
    sensors.motors.escribirLCD("BULTO", "BULTO");
    done = true;
    }}

    return false;
}
void Algorithm::clear(byte ox, byte oy)
{
  pointers auxValor;
  auxValor.px = -1;
  auxValor.py = -1;
  objX = ox;
  objY = oy;

  for(byte i = 0; i < 15; i++)
    {
      for(byte j = 0; j < 15; j++)
        {
          m4p[i][j] = -1;
          save[i][j] = auxValor;
          algorithmVisiteds[i][j] = false;
        }
    }

  for(byte i = 0; i < 100; i++)
    {
      moves[i] = 'z';
    }

  for(byte i = 0; i <15; i++)
  {
    for(byte j = 0; j < 15; j++)
    {
        if(robot.tile[i][j][robot.z].visited() && !robot.tile[i][j][robot.z].blackTile())
            m4p[i][j] = 0;
        if(robot.tile[i][j][robot.z].bumper())
            m4p[i][j] = -2;
    }
  }

  m4p[objX][objY] = 99;
  m4p[robot.x][robot.y] = 0;

  /*for(byte i=0; i<15; i++){
    for(byte j=0;j<15;j++){
      if(m4p[i][j] == -1)
        {
          Serial.print("#");
        }
        else{
      Serial.print(m4p[i][j]);}
      Serial.print("      ");
    }
    Serial.println("");
  }
  Serial.println(" ");*/
}

void Algorithm::startBfs()
{
  QueueArray <costs> sons;
  costs firstCost, secondCost;
  firstCost.node = 0;
  firstCost.a = robot.x;
  firstCost.b = robot.y;
  algorithmVisiteds[robot.x][robot.y] = true;
  sons.push(firstCost);

  while(!sons.isEmpty())
    {
      firstCost = sons.front();
      sons.pop();
      algorithmVisiteds[firstCost.a][firstCost.b] = true;

      if(!algorithmVisiteds[firstCost.a][firstCost.b+1] && m4p[firstCost.a][firstCost.b+1] != -1 && m4p[firstCost.a][firstCost.b+1] != 99 && firstCost.a >= 0 && firstCost.a < 15 && firstCost.b+1 >= 0 && firstCost.b+1 < 15 && !robot.tile[firstCost.a][firstCost.b][robot.z].right())
        {
          if(m4p[firstCost.a][firstCost.b+1] == -2){
            m4p[firstCost.a][firstCost.b+1] = firstCost.node + 10;
            secondCost.node = firstCost.node + 10;
          }else{
            m4p[firstCost.a][firstCost.b+1] = firstCost.node + 1;
            secondCost.node = firstCost.node + 1;
          }
          
          secondCost.a = firstCost.a;
          secondCost.b = firstCost.b+1;
          save[firstCost.a][firstCost.b+1] = {firstCost.a, firstCost.b};
          sons.push(secondCost);
        }

      if(!algorithmVisiteds[firstCost.a][firstCost.b-1] && m4p[firstCost.a][firstCost.b-1] != -1 && m4p[firstCost.a][firstCost.b-1] != 99 && firstCost.a >= 0 && firstCost.a < 15 && firstCost.b-1 >= 0 && firstCost.b-1 < 15 && !robot.tile[firstCost.a][firstCost.b][robot.z].left())
        {
          if(m4p[firstCost.a][firstCost.b-1] == -2){
            m4p[firstCost.a][firstCost.b-1] = firstCost.node + 10;
            secondCost.node = firstCost.node + 10;
          }else{
            m4p[firstCost.a][firstCost.b-1] = firstCost.node + 1;
            secondCost.node = firstCost.node + 1;
          }
          
          secondCost.a = firstCost.a;
          secondCost.b = firstCost.b-1;
          save[firstCost.a][firstCost.b-1] = {firstCost.a,firstCost.b};
          sons.push(secondCost);
        }

      if(!algorithmVisiteds[firstCost.a+1][firstCost.b] && m4p[firstCost.a+1][firstCost.b] != -1 && m4p[firstCost.a+1][firstCost.b] != 99 && firstCost.a+1 >= 0 && firstCost.a+1 < 15 && firstCost.b >= 0 && firstCost.b < 15 && !robot.tile[firstCost.a][firstCost.b][robot.z].down())
        {
          if(m4p[firstCost.a+1][firstCost.b] == -2){
            m4p[firstCost.a+1][firstCost.b] = firstCost.node + 10;
            secondCost.node = firstCost.node + 10;
          }else{
            m4p[firstCost.a+1][firstCost.b] = firstCost.node + 1;
            secondCost.node = firstCost.node + 1;
          }
          
          secondCost.a = firstCost.a+1;
          secondCost.b = firstCost.b;
          save[firstCost.a+1][firstCost.b] = {firstCost.a,firstCost.b};
          sons.push(secondCost);
        }

      if(!algorithmVisiteds[firstCost.a-1][firstCost.b] && m4p[firstCost.a-1][firstCost.b] != -1 && m4p[firstCost.a-1][firstCost.b] != 99 && firstCost.a-1 >= 0 && firstCost.a-1 < 15 && firstCost.b >= 0 && firstCost.b < 15  && !robot.tile[firstCost.a][firstCost.b][robot.z].up())
        {
          if(m4p[firstCost.a-1][firstCost.b] == -2){
            m4p[firstCost.a-1][firstCost.b] = firstCost.node + 10;
            secondCost.node = firstCost.node + 10;
          }else{
            m4p[firstCost.a-1][firstCost.b] = firstCost.node + 1;
            secondCost.node = firstCost.node + 1;
          }

          secondCost.a = firstCost.a-1;
          secondCost.b = firstCost.b;
          save[firstCost.a-1][firstCost.b] = {firstCost.a,firstCost.b};
          sons.push(secondCost);
        }
    }

 /*  for(byte i=0; i<15; i++){
    for(byte j=0;j<15;j++){
      if(m4p[i][j] == -1)
        {
          Serial.print("#");
        }
        else{
      Serial.print(m4p[i][j]);}
      Serial.print("      ");
    }
    Serial.println("");
  }
  Serial.println(" ");*/
}

void Algorithm::findWay()
{
  contador = 0;
  menor = 100;
  BFSx = objX;
  BFSy = objY;

  while(m4p[BFSx][BFSy] != 0)
    {
      if((m4p[BFSx][BFSy+1] < menor) && (m4p[BFSx][BFSy+1] != -1) && (algorithmVisiteds[BFSx][BFSy+1] == true) && BFSx >= 0 && BFSy+1 >= 0 && BFSx < 15 && BFSy+1 < 15 && (!robot.tile[BFSx][BFSy][robot.z].right()))
        {
          menor = m4p[BFSx][BFSy+1];
          moves[contador] = 'i';
        }

      if((m4p[BFSx+1][BFSy] < menor) && (m4p[BFSx+1][BFSy] != -1) && (algorithmVisiteds[BFSx+1][BFSy] == true) && BFSx+1 >= 0 && BFSy >= 0 && BFSx+1 < 15 && BFSy < 15 && (!robot.tile[BFSx][BFSy][robot.z].down()))
       {
          menor = m4p[BFSx+1][BFSy];
          moves[contador] = 'f';
        }

      if((m4p[BFSx-1][BFSy] < menor) && (m4p[BFSx-1][BFSy] != -1) && (algorithmVisiteds[BFSx-1][BFSy] == true) && BFSx-1 >= 0 && BFSy >= 0 && BFSx-1 < 15 && BFSy < 15 && (!robot.tile[BFSx][BFSy][robot.z].up()))
        {
          menor = m4p[BFSx-1][BFSy];
          moves[contador] = 'a';
        }

      if((m4p[BFSx][BFSy-1] < menor) && (m4p[BFSx][BFSy-1] != -1) && (algorithmVisiteds[BFSx][BFSy-1] == true) && BFSx >= 0 && BFSy-1 >= 0 && BFSx < 15 && BFSy-1 < 15 && (!robot.tile[BFSx][BFSy][robot.z].left()))
        {
          menor = m4p[BFSx][BFSy-1];
          moves[contador] = 'd';
        }

      if(moves[contador] == 'i')
        {
          BFSy++;
        }
        else if(moves[contador] == 'f')
          {
            BFSx++;
          }
          else if(moves[contador] == 'a')
            {
              BFSx--;
            }
            else if(moves[contador] == 'd')
              {
                BFSy--;
              }

     //Serial.println(moves[contador]);

     contador++;
    }

    char movesOf[contador];

    for(byte i = 0, j = contador - 1; i < contador; i++, j--)
      {
        movesOf[i] = moves[j];
      }

    for(byte i = 0; i < contador; i++)
      {
        if(i == contador - 1)
        {
          if(movesOf[i] == 'a')
          {
            switch(robot.getDirection())
              {
                case 'N':
                {
                  this -> halfTurn();
                } break;
                case 'E':
                {
                  this -> rightTurn();
                } break;
                case 'W':
                {
                  this -> leftTurn();
                } break;
                case 'S':
                {
                } break;
              }
          }
          else if(movesOf[i] == 'd')
            {
              switch(robot.getDirection())
              {
                case 'N':
                {
                  this -> rightTurn();
                } break;
                case 'E':
                {
                } break;
                case 'W':
                {
                this -> halfTurn();

                } break;
                case 'S':
                {
                  this -> leftTurn();
                } break;
              }
            }
            else if(movesOf[i] == 'i')
              {
                switch(robot.getDirection())
                  {
                    case 'N':
                    {
                      this -> leftTurn();
                    } break;
                    case 'E':
                    {
                      this -> halfTurn();

                    } break;
                    case 'W':
                    {
                    } break;
                    case 'S':
                    {
                      this -> rightTurn();
                    } break;
                  }
              }
              else if(movesOf[i] == 'f')
                {
                  switch(robot.getDirection())
                    {
                      case 'N':
                      {
                      } break;
                      case 'E':
                      {
                        this -> leftTurn();
                      } break;
                      case 'W':
                      {
                        this -> rightTurn();
                      } break;
                      case 'S':
                      {
                   this -> halfTurn();
                      } break;
                    }
                }
        }
        else
        {
          if(movesOf[i] == 'a')
            {
              switch(robot.getDirection())
                {
                  case 'N':
                  {
                  this -> halfTurn();
                    this -> forwardAlg();
                  } break;
                  case 'E':
                  {
                    this -> rightTurn();
                    this -> forwardAlg();
                  } break;
                  case 'W':
                  {
                    this -> leftTurn();
                    this -> forwardAlg();
                  } break;
                  case 'S':
                  {
                    this -> forwardAlg();
                  } break;
                }
            }
            else if(movesOf[i] == 'd')
              {
                switch(robot.getDirection())
                {
                  case 'N':
                  {
                    this -> rightTurn();
                    this -> forwardAlg();
                  } break;
                  case 'E':
                  {
                    this -> forwardAlg();
                  } break;
                  case 'W':
                  {
                    this -> halfTurn();
                    this -> forwardAlg();
                  } break;
                  case 'S':
                  {
                    this -> leftTurn();
                    this -> forwardAlg();
                  } break;
                }
              }
              else if(movesOf[i] == 'i')
                {
                  switch(robot.getDirection())
                    {
                      case 'N':
                      {
                        this -> leftTurn();
                        this -> forwardAlg();
                      } break;
                      case 'E':
                      {
                        this -> halfTurn();
                        this -> forwardAlg();
                      } break;
                      case 'W':
                      {
                        this -> forwardAlg();
                      } break;
                      case 'S':
                      {
                        this -> rightTurn();
                        this -> forwardAlg();
                      } break;
                    }
                }
                else if(movesOf[i] == 'f')
                  {
                    switch(robot.getDirection())
                      {
                        case 'N':
                        {
                          this -> forwardAlg();
                        } break;
                        case 'E':
                        {
                          this -> leftTurn();
                          this -> forwardAlg();
                        } break;
                        case 'W':
                        {
                          this -> rightTurn();
                          this -> forwardAlg();
                        } break;
                        case 'S':
                        {                  
                          this -> halfTurn();
                          this -> forwardAlg();
                        } break;
                      }
                  }
      }
  }
}

void Algorithm::forwardAlg()
{
    sensors.motors.rightCount = 0;

  int newTic = sensors.motors.tic1;
  int dE = sensors.getDistanceOf(3);
  int bb = 0 ;
  bool fT = true;
  int crash=0;
  uint8_t tam = 0;
  int maxTam=0;
  int dIn = sensors.getDistanceOf(3);
  sensors.motors.bumperControl=false;

 /* if(dIn<18)
  return; */
  
  sensors.motors.setBase(230);
  
while(sensors.motors.rightCount<newTic)
{
 sensors.motors.avanzar(sensors.motors.de, sensors.getDistanceOf(1), sensors.getDistanceOf(2), bb);

      if(sensors.motors.rightCount<(newTic * 0.60))
       {
        
        if(digitalRead(sensors.motors.pin1)==HIGH)
          {
            crash++;
            if(crash==4)return;
            sensors.motors.choqueDer(sensors.motors.de, 65);
            sensors.motors.rightCount=0;
          }
          if(digitalRead(sensors.motors.pin3)==HIGH)
          {
            crash++;
            if(crash==4)return;
            sensors.motors.choqueIzq(sensors.motors.de, 65);
            sensors.motors.rightCount=0;
          }
        if(digitalRead(sensors.motors.pin5)==HIGH)
          {
            crash++;
            if(crash==4)return;
            sensors.motors.choqueIzq(sensors.motors.de, 40);
            sensors.motors.rightCount=0;
          }
        if(digitalRead(sensors.motors.pin4)==HIGH)
          {
            crash++;
            if(crash==4)return;
            sensors.motors.choqueDer(sensors.motors.de, 40);
            sensors.motors.rightCount=0;
          }
        if(digitalRead(sensors.motors.pin2)==HIGH)
          {
            crash++;
            if(crash==4)return;
            sensors.motors.choqueDer(sensors.motors.de, 20);
            sensors.motors.rightCount=0;
          }
        if(digitalRead(sensors.motors.pin6)==HIGH)
          {
            crash++;
            if(crash==4)return;
            sensors.motors.choqueIzq(sensors.motors.de, 20);
            sensors.motors.rightCount=0;
          }
       }

     if(bb>0)
       {
        newTic= newTic + bb*24;
        bb = 0;
        sensors.motors.bT=true;
       }
    

if(!sensors.motors.bumperControl)
{
if(sensors.motors.bumper(tam)){
sensors.motors.bumperControl=true;
maxTam=tam;
}
}
else if(fT)
{
sensors.motors.bumper(tam);
sensors.motors.bumperControl=true;
if(tam>=maxTam)
maxTam = tam;
else if (fT){
newTic= newTic+maxTam*70;
fT=false;
}

}

}
sensors.motors.detenerse();
sensors.motors.checar();
delay(50);
sensors.checkDistances();
sensors.motors.setBase(sensors.motors.velInicial);
}
void Algorithm::moveForward(bool &perfect)
{  
  
  sensors.motors.rightCount = 0;
  
   int bb = 0;
   uint8_t maxTam = 0;
   int crash = 0;
   uint8_t tam = 0 ;
   int newTic = sensors.motors.tic1;
   sensors.motors.bT=false;
   bool vieneDeBumper=false;
   if( sensors.motors.bumperControl)
   vieneDeBumper=true;
   else
   vieneDeBumper=false;
   
   sensors.motors.bumperControl=false;
   bool fT = true;
   int aux;
   double diE = sensors.getDistanceOf(3);
   double diA = sensors.getDistanceOf(4);
   bool visualV = false;
   bool heatV = false;
   bool trueRamp = false;
   negroCount  = 0;
   bool band = false;  
  
if(sensors.motors.bumper(tam) || vieneDeBumper)
{
  fT=false;
  newTic+=tam*150;
  
  if(sensors.motors.bumper(tam))
  sensors.motors.bumperControl=true;
  
  maxTam=tam;
  sensors.motors.setBase(240);
  band=true;
  robot.tile[robot.x][robot.y][robot.z].bumper(1);
     digitalWrite(37,HIGH);

  //ACTUAL
}
else{
  sensors.motors.setBase(sensors.motors.velInicial);
     digitalWrite(37,LOW);
}

if(visualVictim())
visualV=true;

if(heatVictim())
heatV=true;

  while(sensors.motors.rightCount < newTic)
    {

      //sensors.motors.escribirLetraLCD(camaraChar);
      if(band)
      {
        if(sensors.motors.rightCount >  newTic*0.2)
         sensors.motors.setBase(195);
        else if(sensors.motors.rightCount > newTic*0.4)
          sensors.motors.setBase(sensors.motors.velInicial);
      }
      
      sensors.motors.avanzar(sensors.motors.de, sensors.getDistanceOf(1), sensors.getDistanceOf(2), bb);
      //blackSquare = sensors.motors.cuadroNegro();
      //(blackSquare) ? digitalWrite(37, HIGH) : digitalWrite(37, LOW);
      value = sensors.motors.rampa(sensors.motors.de);

      bool s =true;

if(value!=0){
  if(value==1)
s=true;
else if(value==2)
s=false;

unsigned long mm = millis();

      while(sensors.motors.condRampa(s))
      {
       sensors.motors.avanzar(sensors.motors.de, sensors.getDistanceOf(1), sensors.getDistanceOf(2), bb);

     if(sensors.motors.rightCount>3500)
        trueRamp=true;
        else
        trueRamp=false;

       if(millis()>(mm+6000))
       sensors.motors.setBase(sensors.motors.velInicial+66);
       
      }

if(trueRamp){
unsigned long te = millis();

while(millis()<(te+370))
sensors.motors.avanzar(sensors.motors.de, sensors.getDistanceOf(1), sensors.getDistanceOf(2), bb);

sensors.motors.detenerse();
sensors.motors.setBase(sensors.motors.velInicial);
sensors.motors.girosX=3;

//sensors.motors.actualizaSetPoint(sensors.motors.de);
//delay(50);

//sensors.motors.actualizaSetPointY();

  if(value == 1)
  {
    robot.tile[robot.x][robot.y][robot.z].upRamp(1);
    robot.tile[robot.x][robot.y][robot.z].downRamp(1);
  }
  else if(value == 2)
  {
    robot.tile[robot.x][robot.y][robot.z].downRamp(1);
    robot.tile[robot.x][robot.y][robot.z].upRamp(1);
  }

        switch(robot.getDirection())
        {
          case 'N': robot.tile[robot.x-1][robot.y][robot.z].visited(1);
          break;
          case 'E': robot.tile[robot.x][robot.y+1][robot.z].visited(1);
          break;
          case 'W': robot.tile[robot.x][robot.y-1][robot.z].visited(1);
          break;
          case 'S': robot.tile[robot.x+1][robot.y][robot.z].visited(1);
          break;
        }

        if(value == 1)
          robot.z++;
        else if(value == 2)
          robot.z--;

        if(robot.z == -1)
          robot.dataTransferDownFloor();
        else if(robot.z == 4)
          robot.dataTransferUpFloor();
          
      if(value == 1)
      {
        switch(robot.getDirection())
        {
          case 'N': robot.tile[robot.x-1][robot.y][robot.z].upRamp(1);
          break;
          case 'E': robot.tile[robot.x][robot.y+1][robot.z].upRamp(1);
          break;
          case 'W': robot.tile[robot.x][robot.y-1][robot.z].upRamp(1);
          break;
          case 'S': robot.tile[robot.x+1][robot.y][robot.z].upRamp(1);
          break;
        }
      }
      else if(value == 2)
      {
        switch(robot.getDirection())
        {
          case 'N': robot.tile[robot.x-1][robot.y][robot.z].downRamp(1);
          break;
          case 'E': robot.tile[robot.x][robot.y+1][robot.z].downRamp(1);
          break;
          case 'W': robot.tile[robot.x][robot.y-1][robot.z].downRamp(1);
          break;
          case 'S': robot.tile[robot.x+1][robot.y][robot.z].downRamp(1);
          break;
        }
      }
      
}
}
    if(!heatV)
     {
      if(heatVictim())
      heatV=true;
     }

     if(!visualV)
     {
      if(visualVictim())
      visualV=true;
     }
     
     
      if(sensors.motors.rightCount<(newTic * 0.60))
       {
        
        if(digitalRead(sensors.motors.pin1)==HIGH)
          {
            crash++;
            if(crash==4)return;
            sensors.motors.choqueDer(sensors.motors.de, 65);
            sensors.motors.rightCount=0;
          }
          if(digitalRead(sensors.motors.pin3)==HIGH)
          {
            crash++;
            if(crash==4)return;
            sensors.motors.choqueIzq(sensors.motors.de, 65);
            sensors.motors.rightCount=0;
          }
        if(digitalRead(sensors.motors.pin5)==HIGH)
          {
            crash++;
            if(crash==4)return;
            sensors.motors.choqueIzq(sensors.motors.de, 40);
            sensors.motors.rightCount=0;
          }
        if(digitalRead(sensors.motors.pin4)==HIGH)
          {
            crash++;
            if(crash==4)return;
            sensors.motors.choqueDer(sensors.motors.de, 40);
            sensors.motors.rightCount=0;
          }
        if(digitalRead(sensors.motors.pin2)==HIGH)
          {
            crash++;
            if(crash==4)return;
            sensors.motors.choqueDer(sensors.motors.de, 20);
            sensors.motors.rightCount=0;
          }
        if(digitalRead(sensors.motors.pin6)==HIGH)
          {
            crash++;
            if(crash==4)return;
            sensors.motors.choqueIzq(sensors.motors.de, 20);
            sensors.motors.rightCount=0;
          }
       }

     if(bb>0)
       {
        newTic= newTic + bb*20;
        bb = 0;
        sensors.motors.bT=true;
       }
    

if(!sensors.motors.bumperControl)
{
if(sensors.motors.bumper(tam)){
sensors.motors.bumperControl=true;
maxTam=tam;
if(sensors.motors.rightCount<newTic/2)
robot.tile[robot.x][robot.y][robot.z].bumper(1);
else
{
  switch(robot.getDirection())
  {
    case 'N': robot.tile[robot.x-1][robot.y][robot.z].bumper(1);
      break;
    case 'E': robot.tile[robot.x][robot.y+1][robot.z].bumper(1);
      break;
    case 'W': robot.tile[robot.x][robot.y-1][robot.z].bumper(1);
      break;
    case 'S': robot.tile[robot.x+1][robot.y][robot.z].bumper(1);
      break;
  }
}
}
}
else if(fT)
{
sensors.motors.bumper(tam);
sensors.motors.bumperControl=true;
if(tam>=maxTam)
maxTam = tam;
else if (fT){
newTic= newTic+maxTam*70;
fT=false;
}

}

}
  sensors.motors.detenerse();
  sensors.motors.checar();
  delay(200);

  if(sensors.motors.bumperControl || vieneDeBumper)
   { 
    sensors.acomodo(diE,diA);
     digitalWrite(37,HIGH);
   }
   else
     digitalWrite(37,LOW);

  
  sensors.checkDistances();
}

void Algorithm::rightTurn()
{
    robot.changeDirection(1, robot.getDirection());

    (sensors.motors.de == 270) ? sensors.motors.de = 0 : sensors.motors.de += 90;
    sensors.motors.giro(sensors.motors.de);
    sensors.motors.detenerse();
     delay(155);

    sensors.motors.checar();

    //sensors.motors.escribirLetraLCD(robot.getDirection());
    //delay(1000);

    if(sensors.getDistanceOf(4) <= 21 && !sensors.motors.bumperControl && ((sensors.motors.girosX>2 || sensors.getDistanceOf(3)==0)))
    {
      sensors.motors.atrasSN();
      sensors.motors.girosX=0;
    }
    else
      sensors.motors.girosX++;
        
      sensors.checkDistances();

}

void Algorithm::leftTurn()
{
    robot.changeDirection(3, robot.getDirection());
    (sensors.motors.de == 0) ? sensors.motors.de = 270 : sensors.motors.de -= 90;
    sensors.motors.giro(sensors.motors.de);
    sensors.motors.detenerse();
    delay(155);

    sensors.motors.checar();

    //sensors.motors.escribirLetraLCD(robot.getDirection());

    if(sensors.getDistanceOf(4) <= 21 && !sensors.motors.bumperControl && (sensors.motors.girosX>2 || sensors.getDistanceOf(3)==0))
      {sensors.motors.atrasSN();
      sensors.motors.girosX=0;
      }
    else
      sensors.motors.girosX++;

        sensors.checkDistances();
}
void Algorithm::halfTurn()
{
  robot.changeDirection(1,robot.getDirection());
  robot.changeDirection(1,robot.getDirection());
  
  int n =   sensors.motors.de+180;
  n= n%360;
  sensors.motors.de=n;
  
    sensors.motors.giro(sensors.motors.de);
    sensors.motors.detenerse();
    delay(155);

    sensors.motors.checar();

    if(sensors.getDistanceOf(4) <= 21 && !sensors.motors.bumperControl)
      {
      sensors.motors.atrasSN();
      sensors.motors.girosX=0;
      } 
}
