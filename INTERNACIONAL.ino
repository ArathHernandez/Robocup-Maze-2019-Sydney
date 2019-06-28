#include "Movement.h"

Movement all;

int dIe, dId, dIi;

void rightEncoderEvent()
{
  all.maze.sensors.motors.rightCount++;
}

void infiniteLoop()
{
  int a = 0;
  bool p = true;

  if(all.maze.robot.x == all.maze.robot.startX && all.maze.robot.y == all.maze.robot.startY)
  all.maze.sensors.motors.detenerse();
  else
    all.maze.moveForward(p);

  
    
  all.maze.sensors.motors.escribirLCD("END OF ROUND", "ROBORREGOS 2019");

  while(a == 0)
    delay(8000);
}

void setup() {
  Serial.begin(115200);
  
  attachInterrupt(digitalPinToInterrupt(2),rightEncoderEvent, CHANGE);
  //attachInterrupt(digitalPinToInterrupt(50),visualVictim, CHANGE);
  all.maze.setup();
  all.maze.robot.dispenser.setup();
  all.maze.sensors.setup();
  all.maze.sensors.motors.setup();

  if(all.maze.sensors.getDistanceOf(4) > 20)
  {
    all.maze.robot.tile[7][7][1].down(0, &all.maze.robot.tile[7+1][7][1]);
    all.maze.robot.tile[7+1][7][1].exist(1);
    all.maze.robot.tile[7+1][7][1].pending(1);
    all.maze.sensors.motors.actualizaSetPoint(0);
  }
  else{
    all.maze.robot.tile[7][7][1].down(1, &all.maze.robot.tile[7+1][7][1]);
      all.maze.sensors.motors.atras1();
}

dIe = all.maze.sensors.getDistanceOf(3);
delay(10);
dId = all.maze.sensors.getDistanceOf(2);
delay(10);
dIi = all.maze.sensors.getDistanceOf(1);
delay(10);
  
 all.maze.robot.changeSquare(&all.maze.robot.tile[7][7][1], dId, dIi, dIe, all.maze.robot.getDirection());
 all.maze.robot.tile[7][7][1].exist(1);
 all.maze.robot.tile[7][7][1].visited(1);
 all.maze.robot.tile[7][7][1].pending(0);
 

 if(!all.maze.robot.tile[7][7][1].down())
 {
  all.maze.robot.sFxs[all.maze.robot.secondCount] = 7+1;
  all.maze.robot.sFys[all.maze.robot.secondCount] = 7;
  all.maze.robot.secondCount++;
 }

 if(!all.maze.robot.tile[7][7][1].left())
 {
  all.maze.robot.sFxs[all.maze.robot.secondCount] = 7;
  all.maze.robot.sFys[all.maze.robot.secondCount] = 7-1;
  all.maze.robot.secondCount++;
  all.maze.robot.tile[7][7-1][1].exist(1);
  all.maze.robot.tile[7][7-1][1].pending(1);
 }

 if(!all.maze.robot.tile[7][7][1].right())
 {
  all.maze.robot.sFxs[all.maze.robot.secondCount] = 7;
  all.maze.robot.sFys[all.maze.robot.secondCount] = 7+1;
  all.maze.robot.secondCount++;
  all.maze.robot.tile[7][7+1][1].exist(1);
  all.maze.robot.tile[7][7+1][1].pending(1);
 }


//  Serial.println(all.maze.sensors.getDistanceOf(sensors.echo_A, 4));
 
}

void loop() { 
  (all.endOfRound) ? infiniteLoop() : all.moveOn();
}
