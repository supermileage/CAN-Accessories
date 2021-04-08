#include "mbed.h"
#include "Accessory.h"
#include <string>

#define BLINK_RATE 0.5

Accessory::Accessory(PinName pin, int initialState, bool blinks, int id, int board, string name) : accessory(pin){
    Serial pc(USBTX, USBRX);
    pc.printf("Intializing %s to default state %s\n", name.c_str(), initialState ? "ON" : "OFF");
    wait(0.01); //This is here to prevent Serial output from getting garbled up. (And so we can remove it later on and claim that we improved load speeds by 50%)
    accessory = initialState;
    currentState = initialState;
    if (currentState && blinks) {
        pc.printf("Attaching %s to ticker\n", name.c_str());
        t.attach(callback(this, &Accessory::blink), BLINK_RATE);
    }
    this->blinks = blinks;
    this->id = id;
    this->name = name;
    this->board = board;
}

void Accessory::updateState(int newState) {
    Serial pc(USBTX, USBRX);
    if (currentState != newState){
        pc.printf("%s changed to %s\n", name.c_str(), newState ? "ON" : "OFF");
        //set accessory states
        accessory = newState;
        currentState = newState;
        if ( newState && blinks ) {
            pc.printf("attaching %s to ticker\n", name.c_str());
            t.attach(callback(this, &Accessory::blink), BLINK_RATE);
        } else if (!newState && blinks ) {
            pc.printf("detaching %s from ticker\n", name.c_str());
            t.detach();
            //gotta make sure its toggled correctly lmao
            accessory = newState;
        }
    }
}

void Accessory::blink() {
    accessory = !accessory;
}
