#ifndef LEDTICKER_H
#define LEDTICKER_H
#include "mbed.h"
class LedTicker {
    public:
        DigitalOut accessory;
        LedTicker(PinName pin);
        void start();
        void toggle_acc();
        void stop();
    private:
        Ticker t;
};
#endif