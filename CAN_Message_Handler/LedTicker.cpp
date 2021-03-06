#include "mbed.h"
#include "LedTicker.h"

LedTicker::LedTicker(PinName pin) : accessory(pin){
   accessory = 0;
}
void LedTicker::start(){
    t.attach(callback(this, &LedTicker::toggle_acc), 0.5);
}

void LedTicker::stop(){
    t.detach();
}

void LedTicker::toggle_acc(){
    accessory = !accessory;
}