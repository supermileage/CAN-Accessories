#ifndef ACCESSORY_H
#define ACCESSORY_H

class Accessory {
  public:
    Accessory(PinName pin, int initialState);
    int currentState;
    bool blinks;
    void updateState(int newState);
    void blink();
    int id;
  private:
    DigitalOut accessory;
    Ticker t;
};

#endif
