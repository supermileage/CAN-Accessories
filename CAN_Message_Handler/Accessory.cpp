#include "mbed.h"
#include "Accessory.h"

Accessory::Accessory(PinName pin, int initialState, bool blink) : accessory(pin){
    accessory = initialState;
    currentState = initialState;
    blinks = blink
}

void Accessory::updateState(int newState) {
    accessory = newState;
    currentState = newState;
}

void Accessory::blink() {
    accessory = !accessory;
}
