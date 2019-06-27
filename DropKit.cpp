#include <Arduino.h>
#include "DropKit.h"

DropKit::DropKit(){}

void DropKit::setup()
{
  dispenser.attach(42);
  dispenser.write(90);
}

void DropKit::dropOneKitLeft()
{
  dispenser.write(0);
  delay(1000);
  dispenser.write(100);
  delay(1000);
  dispenser.write(90);
  delay(200);
  
}

void DropKit::dropOneKitRight()
{
  dispenser.write(180);
  delay(1000);
  dispenser.write(80);
  delay(1000);
  dispenser.write(90);
  delay(200);
}

void DropKit::dropTwoKitsLeft()
{
  dispenser.write(0);
  delay(1000);
  dispenser.write(100);
  delay(1000);
  dispenser.write(90);
  delay(200);
  dispenser.write(0);
  delay(1000);
  dispenser.write(100);
  delay(1000);
  dispenser.write(90);
  delay(200);
}

void DropKit::dropTwoKitsRight()
{
  dispenser.write(180);
  delay(1000);
  dispenser.write(80);
  delay(1000);
  dispenser.write(90);
  delay(200);
  dispenser.write(180);
  delay(1000);
  dispenser.write(80);
  delay(1000);
  dispenser.write(90);
  delay(200);
}

