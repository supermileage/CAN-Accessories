#include "mbed.h"
#include "CanHandler.h"
#include "Accessory.h"
#include <iostream>

using namespace std;

CAN can(PA_11, PA_12); // CAN pins

// Initializing all accessories; need proper pinout
Accessory headlights(PB_0, 0, false);
Accessory breaklights(PB_0, 0, false);
Accessory horn(PB_0, 0, false);
Accessory hazards(PB_0, 0, true);
Accessory rightInd(PB_0, 0, true);
Accessory leftInd(PB_0, 0, true);
Accessory wipers(PB_0, 0, false);
Accessory accessories[] = {hazards, rightInd, leftInd, wipers, headlights, breaklights, horn};

CanHandler::CanHandler() {
  can.frequency(500000);
}
void controlBlinking(int id);


/**
* Reads CAN Bus messages and toggles accessories if its state has changed.
*/
void CanHandler::handleMessages() {
  CANMessage msg;

  if (can.read(msg)) {
    for (int i = 0; i < sizeof(accessories); i++) { // Blinking accessories
        if ( (msg.data[0] & (1 << i)) / pow(2,i) != accessories[i].currentState) { // Check if state changes
            accessories[i].updateState(msgState);
            if (accessories[i].blinks) controlBlinking(i);
        }
    }
  }
}

Ticker hazardsT;
Ticker rightIndT;
Ticker leftIndT;

Ticker tickers[] = {hazardsT, rightIndT, leftIndT};

/**
* Helper method to control blinking accessories
* @param: id,
*/
void controlBlinking(int id) {
    int state = accessories[id].currentState;
    if (state) {
        tickers[id].attach(&accessories[id], &Accessory::blink, 0.5);
    } else {
        tickers[id].detach();
    }
}
