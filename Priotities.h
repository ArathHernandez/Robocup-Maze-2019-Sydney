#ifndef Priotities_h
#define Priotities_h

#include <Arduino.h>
#include "Bit.h"
#include "DropKit.h"

class Priotities
{
  public:

    Priotities(uint16_t, uint16_t, uint16_t, char);
    Bit tile[15][15][4];
    DropKit dispenser;
    
    void changeDirection(uint8_t condition, char dir);
    char getDirection();
    bool correctMovementRight(char dir);
    bool correctMovementLeft(char dir);
    bool correctMovementFront(char dir);
    void changeSquare(Bit *actualSquare, int rightDistance, int leftDistance, int frontDistance, char dir);
    void changeStatus(Bit *actualSquare, char dir);
    void changeCoordinates(char dir);
    void correction(char dir);
    void dataTransferUp();
    void dataTransferDown();
    void dataTransferRight();
    void dataTransferLeft();
    void dataTransferUpFloor();
    void dataTransferDownFloor();
    
    uint16_t x;
    uint16_t y;
    uint16_t z;
    uint16_t firstCount = 0;
    uint16_t secondCount = 0;
    uint16_t thirdCount = 0;
    uint16_t fourthCount = 0;
    uint16_t startX;
    uint16_t startY;
    uint16_t startZ;

    uint16_t fFxs[100];
    uint16_t fFys[100];
    uint16_t sFxs[100];
    uint16_t sFys[100];
    uint16_t tFxs[100];
    uint16_t tFys[100];
    uint16_t fhFxs[100];
    uint16_t fhFys[100];

  private:
  
    bool returningVariable;
    char directi0n;
};

#endif

