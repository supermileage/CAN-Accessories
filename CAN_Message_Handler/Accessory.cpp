#include "mbed.h"
#include "Accessory.h"

#define BLINK_RATE 0.5

Accessory::Accessory(PinName pin, int initialState, bool blinks, int id) : accessory(pin){
    accessory = initialState;
    currentState = initialState;
    this->blinks = blinks;
    this->id = id;

}

void Accessory::updateState(int newState) {
    if (currentState != newState){
        accessory = newState;
        currentState = newState;
        if ( newState && blinks ) {
            t.attach(callback(this, &Accessory::blink), BLINK_RATE);
        } else if (!newState && blinks ) {
            t.detach();
        }
    }
}

void Accessory::blink() {
    accessory = !accessory;
}
