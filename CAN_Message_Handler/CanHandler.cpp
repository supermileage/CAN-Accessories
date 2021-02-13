#include "mbed.h"
#include "CanHandler.h"
#include "Accessory.h"

using namespace std;

CAN can(PA_11, PA_12); // CAN pins

// Initializing all accessories; need proper pinout
Accessory headlights(PB_0, 0, false, 0);
Accessory breaklights(PB_0, 0, false, 1);
Accessory horn(PB_0, 0, false, 2);
Accessory hazards(PB_0, 0, true, 3);
Accessory rightInd(PB_0, 0, true, 4);
Accessory leftInd(PB_0, 0, true, 5);
Accessory wipers(PB_0, 0, false, 6);
Accessory accessories[] = {hazards, rightInd, leftInd, wipers, headlights, breaklights, horn};

//constructor
CanHandler::CanHandler() {
  can.frequency(500000);
}

/**
* Reads CAN Bus messages and toggles accessories if its state has changed.
*/
void CanHandler::handleMessages() {
  CANMessage msg;

  if (can.read(msg)) {
    for (int i = 0; i < sizeof(accessories); i++) {
        int msgState = (msg.data[0] & (1 << accessories[i].id)) / pow(2,accessories[i].id);
        if (msgState != accessories[i].currentState) {
            accessories[i].updateState(msgState);
        }
    }
  }
}