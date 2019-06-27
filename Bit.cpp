#include <Arduino.h>
#include "Bit.h"

Bit::Bit() {
  inf1 = inf2 = 0;
}

bool Bit::up() {
  return inf1 & '\x80'; 
}

bool Bit::right() {
  return inf1 & '\x40';
}

bool Bit::down() {
  return inf1 & '\x20';
}

bool Bit::left() {
  return inf1 & '\x10';
}

bool Bit::victim() {
  return inf1 & '\x8';
}

bool Bit::blackTile() {
  return inf1 & '\x4';
}

bool Bit::checkpoint() {
  return inf1 & '\x2';
}

bool Bit::visited() {
  return inf1 & '\x1';
}


uint8_t Bit::flo0r() {
  if(inf2 & '\x20') {
    if(inf2 & '\x40')
      return 3;
    return 2;
  }
  if(inf2 & '\x40')
    return 1;
  return 0;
}

bool Bit::ramp() {
  return inf2 & '\x10';
}

bool Bit::exist() {
  return inf2 & '\x8';
}

bool Bit::start() {
  return inf2 & '\x4';
}

bool Bit::pending() {
  return inf2 & '\x2';
}

bool Bit::bumper() {
  return inf2 & '\x1';
}

//Setters
void Bit::victim(const bool &b) {
  inf1 |= (b<<3);
}

void Bit::blackTile(const bool &b) {
  inf1 |= (b<<2);
}

void Bit::checkpoint(const bool &b) {
  inf1 |= (b<<1);
}

void Bit::visited(const bool &b) {
  inf1 |= b;
}

void Bit::start(const bool &b) {
  inf2 |= (b<<2);
}

void Bit::pending(const bool &b) {
  inf2 |= (b<<1);
}

void Bit::bumper(const bool &b) {
  inf2 |= b;
}

void Bit::ramp(const bool &b) {
  inf2 |= (b<<4);
}

void Bit::flo0r(const int  & i) {
  switch(i) {
  case 0:
    inf2 &= '\xbf'; 
    inf2 &= '\xdf';
    break;
  case 1:
    inf2 |= '\x40';
    inf2 &= '\xdf';
    break;
  case 2:
    inf2 &= '\xbf';
    inf2 |= '\x20';
    break;
  case 3:
    inf2 |= '\x40';
    inf2 |= '\x20';
    break;
  }
}


void Bit::up(const bool &b, Bit *theTop) {
  inf1 |= (b<<7);
  if(theTop)
    theTop->inf1 |= (b<<5);
}

void Bit::right(const bool &b, Bit *theRight) {
  inf1 |= (b<<6);
  if(theRight)
    theRight->inf1 |= (b<<4);
}

void Bit::down(const bool &b, Bit *theDown) {
  inf1 |= (b<<5);
  if(theDown)
    theDown->inf1 |= (b<<7);
}

void Bit::left(const bool &b, Bit *theLeft) {
  inf1 |= (b<<4);
  if(theLeft)
    theLeft->inf1 |= (b<<6);
}

void Bit::exist(const bool &b) {
  inf2 |= (b<<3);
}

char Bit::getInf1()
{
  return inf1;
}

char Bit::getInf2()
{
  return inf2;
}

void Bit::setInf1(char info)
{
  inf1 = info;
}

void Bit::setInf2(char info)
{
  inf2 = info;
}

