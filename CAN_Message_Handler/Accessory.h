#ifndef ACCESSORY_H
#define ACCESSORY_H

class Accessory {
  public:
    Accessory(PinName pin, int initialState);
    int currentState;
    void updateState(int newState);
    void blink();
  private:
    DigitalOut accessory;
};

#endif
