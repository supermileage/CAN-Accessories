#include "mbed.h"
#include "Accessory.h"

Accessory::Accessory(PinName pin, int initialState) : accessory(pin){
    accessory = initialState;
    currentState = initialState;
}

void Accessory::updateState(int newState) {
    accessory = newState;
    currentState = newState;
}

void Accessory::blink() {
    accessory = !accessory;
}
