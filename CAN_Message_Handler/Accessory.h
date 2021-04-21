#ifndef ACCESSORY_H
#define ACCESSORY_H
#include <string>
#include "mbed.h"

class Accessory {
  public:
    Accessory(PinName pin, int initialState, bool blinks, int id, int board, string name = "no name");
    int currentState;
    bool blinks;
    void updateState(int newState);
    void blink();
    int id;
    string name;
    int board;
  private:
    DigitalOut accessory;
    Ticker t;
};

#endif
