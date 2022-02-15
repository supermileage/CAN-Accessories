#include "mbed.h"
#include "Accessory.h"
#include "CanAcc.h"

Accessory::Accessory(PinName pin, int initialState, bool blinks, int id, int board, const char name[32]) : out(pin){
    // set accessory to initial state
    this->out = initialState;
    this->currentState = initialState;

    // attach ticker if applicable
    if (currentState && blinks) {
        t.attach(callback(this, &Accessory::blink), BLINK_RATE);
    }
    this->blinks = blinks;
    this->id = id;
    strcpy(this->name, name);
    this->board = board;
}

// probably should change the output pin assignment here to make it less weird
// Accessory::Accessory() : out(D7) {
//     this->currentState = false;
//     this->blinks = false;
//     this->id = 0;
//     strcpy(this->name, "no name brand chocolate milk");
//     this->board = 0;
// }

void Accessory::updateState(bool newState) {
    // only update if different.
    if (currentState != newState){

        currentState = newState;

        if ( newState && blinks ) {     // accessory blinks?
            out = newState;             // must happen before the ticker is attached.
            t.attach(callback(this, &Accessory::blink), BLINK_RATE);
        } else if (!newState && blinks ) {      // accessory blinks but was turned off?
            t.detach();
            out = newState;
        } else {
            out = newState;         // gotta do this everytime.
        }
    }
}

void Accessory::blink() {
    out = !out;
}
