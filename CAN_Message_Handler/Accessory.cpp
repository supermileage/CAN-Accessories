#include "mbed.h"
#include "Accessory.h"

#define BLINK_RATE 0.5

Accessory::Accessory(PinName pin, int initialState, bool blink) : accessory(pin){
    accessory = initialState;
    currentState = initialState;
    blinks = blink;
}

void Accessory::updateState(int newState) {
    if (currentState != newState){
        accessory = newState;
        currentState = newState;
        if ( newState && blink ) {
            t.attach(callback(this, &Accessory::blink), BLINK_RATE);
        } else if (!newState && blink ) {
            t.detach();
        }
    }
}

void Accessory::blink() {
    accessory = !accessory;
}
