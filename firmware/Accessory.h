#ifndef ACCESSORY_H
#define ACCESSORY_H
#include <string>
#include "mbed.h"

class Accessory {
  public:
    Accessory(PinName pin, int initialState, bool blinks, int id, int board, const char name[32] = "no name");
    //Accessory();
    int currentState;
    bool blinks;
    void updateState(bool newState);
    void blink();
    int id;
    char name[32];
    int board;
  private:
    DigitalOut out;
    Ticker t;
};

#endif
