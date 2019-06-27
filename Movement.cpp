#include <Arduino.h>
#include "Movement.h"

Movement::Movement(){}

void Movement::moveOn()
{
  bool perfect = true;
  
/*  if(maze.sensors.getDistanceOf(3) <= 20)
  {
    maze.robot.correction(maze.robot.getDirection());
    this -> conditionOne();
  }
  else
  {*/
     maze.sensors.motors.escribirNumLCD(maze.sensors.getDistanceOf(3));
    delay(1000);
    maze.sensors.motors.escribirNumLCD(maze.sensors.getDistanceOf(2));
    delay(1000);
    maze.sensors.motors.escribirNumLCD(maze.sensors.getDistanceOf(1));
    delay(1000);
    
    maze.moveForward(perfect);
    delay(270);
    this -> isBlack();
  //}
}

void Movement::isBlack()
{
  //maze.sensors.motors.escribirLCD("Revisando Color", "de cuadro");
  ////delay(500);
  
  (maze.sensors.motors.cuadroNegro()) ? this -> responseBlack() : this -> responseNoBlack();  
}

void Movement::responseNoBlack()
{
  //maze.sensors.motors.escribirLCD("No es", "cuadro negro");
  //delay(500);
 // int hola = 0;
 
  maze.robot.changeCoordinates(maze.robot.getDirection());
  
  /*if(hola == 1)
    maze.sensors.motors.escribirLCD("TRANSFIRIENDO", "ARRIBA");
  else if(hola == 2)
    maze.sensors.motors.escribirLCD("TRANSFIRIENDO", "ABAJO");
  else if(hola == 3)
    maze.sensors.motors.escribirLCD("TRANSFIRIENDO", "DERECHA");
  else if(hola == 4)
    maze.sensors.motors.escribirLCD("TRANSFIRIENDO", "IZUIERDA");
  else
    maze.sensors.motors.escribirLCD("NADA", "NADA");
  delay(1500);*/
  //maze.sensors.motors.escribirLetraLCD(maze.robot.getDirection());
  ////delay(500);
  
  maze.robot.changeSquare(&maze.robot.tile[maze.robot.x][maze.robot.y][maze.robot.z], maze.sensors.getDistanceOf(2), maze.sensors.getDistanceOf(1), maze.sensors.getDistanceOf(3), maze.robot.getDirection());
  
  //maze.sensors.motors.escribirNumLCD(maze.robot.x);
  //delay(500);
 //maze.sensors.motors.escribirNumLCD(maze.robot.y);
 //delay(500);
 // maze.sensors.motors.escribirLCD("EMPEZO EN", " ");
 // delay(500);
 // maze.sensors.motors.escribirNumLCD(maze.robot.startX);
  //delay(500);
  //maze.sensors.motors.escribirNumLCD(maze.robot.startY);
  //delay(500);
 //maze.sensors.motors.escribirNumLCD(maze.robot.z);
 //delay(500);

 // maze.sensors.motors.printLoc(maze.robot.x,maze.robot.y,maze.robot.z);
 //delay(500);
 
  maze.robot.changeStatus(&maze.robot.tile[maze.robot.x][maze.robot.y][maze.robot.z], maze.robot.getDirection());

  this -> conditionOne();
}

void Movement::responseBlack()
{
  //maze.sensors.motors.escribirLCD("Caudro negro", "detectado");

  maze.sensors.motors.rightCount = 0;
  maze.sensors.motors.girosX=3;
  

  while(maze.sensors.motors.rightCount < maze.sensors.motors.tic1)
    maze.sensors.motors.atrasPID(maze.sensors.motors.de);

  switch(maze.robot.getDirection())
  {
    case 'N':
    {
      maze.robot.tile[maze.robot.x-1][maze.robot.y][maze.robot.z].blackTile(1);
      maze.robot.tile[maze.robot.x-1][maze.robot.y][maze.robot.z].visited(1);
      maze.robot.tile[maze.robot.x-1][maze.robot.y][maze.robot.z].pending(0);
    } break;
    case 'E':
    {
      maze.robot.tile[maze.robot.x][maze.robot.y+1][maze.robot.z].blackTile(1);
      maze.robot.tile[maze.robot.x][maze.robot.y+1][maze.robot.z].visited(1);
      maze.robot.tile[maze.robot.x][maze.robot.y+1][maze.robot.z].pending(0);
    }  break;
    case 'W':
    {
      maze.robot.tile[maze.robot.x][maze.robot.y-1][maze.robot.z].blackTile(1);
      maze.robot.tile[maze.robot.x][maze.robot.y-1][maze.robot.z].visited(1);
      maze.robot.tile[maze.robot.x][maze.robot.y-1][maze.robot.z].pending(0);
    } break;
    case 'S':
    {
      maze.robot.tile[maze.robot.x+1][maze.robot.y][maze.robot.z].blackTile(1);
      maze.robot.tile[maze.robot.x+1][maze.robot.y][maze.robot.z].visited(1);
      maze.robot.tile[maze.robot.x+1][maze.robot.y][maze.robot.z].pending(0);
    } break;
  }

  this -> conditionOne();
}

void Movement::conditionOne()
{
  //maze.sensors.motors.escribirLCD("Entrando", "a condicion 1");
  //delay(500);

  (maze.robot.correctMovementRight(maze.robot.getDirection())) ? maze.rightTurn() : this -> conditionTwo();
}

void Movement::conditionTwo()
{
  //maze.sensors.motors.escribirLCD("Entrando", "a condicion 2");
  //delay(500);

  if(maze.robot.correctMovementFront(maze.robot.getDirection()))
  {}
  else
    this -> conditionThree();
}

void Movement::conditionThree()
{

  //maze.sensors.motors.escribirLCD("Entrando", "a condicion 3");
  //delay(500);

  (maze.robot.correctMovementLeft(maze.robot.getDirection())) ? maze.leftTurn() : this -> conditionFour();
}

void Movement::conditionFour()
{
  //maze.sensors.motors.escribirLCD("Entrando", "a condicion 4");
  //delay(500);
  countPendings = 0;

  if(maze.robot.z == 0)
  {
    for(int i = maze.robot.firstCount - 1; i >= 0; i--)
    {
      if(!maze.robot.tile[maze.robot.fFxs[i]][maze.robot.fFys[i]][0].visited() && maze.robot.tile[maze.robot.fFxs[i]][maze.robot.fFys[i]][0].exist())
      {
          xA = maze.robot.fFxs[i];
          yA = maze.robot.fFys[i];
          countPendings++;
          i = 0;
      }
    }
  }
  else if(maze.robot.z == 1)
  {
    for(int i = maze.robot.secondCount - 1; i >= 0; i--)
    {
      if(!maze.robot.tile[maze.robot.sFxs[i]][maze.robot.sFys[i]][1].visited() && maze.robot.tile[maze.robot.sFxs[i]][maze.robot.sFys[i]][1].exist())
      {
        xA = maze.robot.sFxs[i];
        yA = maze.robot.sFys[i];
        countPendings++;
        i = 0;
      }
    }
  }
  else if(maze.robot.z == 2)
  {
    for(int i = maze.robot.thirdCount - 1; i >= 0; i--)
    {
      if(!maze.robot.tile[maze.robot.tFxs[i]][maze.robot.tFys[i]][2].visited() && maze.robot.tile[maze.robot.tFxs[i]][maze.robot.tFys[i]][2].exist())
      {
        xA = maze.robot.tFxs[i];
        yA = maze.robot.tFys[i];
        countPendings++;
        i = 0;
      }
    }
  }
  else if(maze.robot.z == 3)
  {
    for(int i = maze.robot.fourthCount - 1; i >= 0; i--)
    {
      if(!maze.robot.tile[maze.robot.fhFxs[i]][maze.robot.fhFys[i]][3].visited() && maze.robot.tile[maze.robot.fhFxs[i]][maze.robot.fhFys[i]][3].exist())
      {
        xA = maze.robot.fhFxs[i];
        yA = maze.robot.fhFys[i];
        countPendings++;
        i = 0;
      }
    }
  }

  if(countPendings == 0)
  {
    xA = maze.robot.startX;
    yA = maze.robot.startY;
    zA = maze.robot.startZ;
    endOfRound = true;

    if(maze.robot.z > zA)
    {
      for(int i = 0; i < 15; i++)
      {
        for(int j = 0; j < 15; j++)
        {
          if(maze.robot.tile[i][j][maze.robot.z].ramp())
          {
            xA = i;
            yA = j;
            endOfRound = false;
            i = 16;
            j = 16;
          }
        }
      }
    }

    //if(maze.robot.x==maze.robot.startX && maze.robot.y==maze.robot.startY  && maze.robot.z==maze.robot.startZ)
    //delay(30000);
    
  }

  //maze.sensors.motors.escribirNumLCD(xA);
  //delay(1000);
  //maze.sensors.motors.escribirNumLCD(yA);
  //delay(1000);

  maze.clear(xA, yA);
  maze.startBfs();
  maze.findWay();

  switch(maze.robot.getDirection())
    {
      case 'N':
        {
          maze.robot.x = xA+1;
          maze.robot.y = yA;
        } break;
      case 'E':
        {
          maze.robot.x = xA;
          maze.robot.y = yA-1;
        } break;
      case 'W':
        {
          maze.robot.x = xA;
          maze.robot.y = yA+1;
        } break;
      case 'S':
        {
          maze.robot.x = xA-1;
          maze.robot.y = yA;
        } break;
    }
}

