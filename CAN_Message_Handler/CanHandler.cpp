#include "mbed.h"
#include "CanHandler.h"
#include "Accessory.h"

using namespace std;

CAN can(PA_11, PA_12); // CAN pins
Serial pc(USBTX, USBRX);

// Initializing all accessories; need proper pinout
Accessory headlights(PB_0, 0, true, 0, "headlights");
Accessory breaklights(PB_7, 0, false, 1, "breaklights");
Accessory horn(PB_6, 0, true, 2, "horn");
Accessory hazards(LED1, 1, true, 3, "hazards");
Accessory rightInd(PB_5, 0, true, 4, "right indicator");
Accessory leftInd(PB_5, 0, true, 5, "left indicator");
Accessory wipers(PB_5, 0, false, 6, "wipers");
Accessory something_else_i_dont_know(PB_0, 0, false, 7);
//accessories are in pointer array because Ticker are not allowed to be copied. It took me 4 hours to fix this bug.
Accessory *accessories[] = {&hazards, &rightInd, &leftInd, &wipers, &headlights, &breaklights, &horn};

//constructor
CanHandler::CanHandler() {
  pc.printf("CanHandler initializing - Setting CAN frequency to 500khz\n");
  wait(0.01); //This is here to prevent Serial output from getting garbled up. (And so we can remove it later on and claim that we improved load speeds by 50%)
  can.frequency(500000);
}

/**
* Reads CAN Bus messages and toggles accessories if its state has changed.
*/
void CanHandler::handleMessages() {
  CANMessage msg;
  if (can.read(msg)) {
    pc.printf("###########################################################\n");
    pc.printf("Message received: ");
    for (int i = 7; i >=0; --i){
      bool bit = ((msg.data[0] & 1 << i) >> i) == 1;
      pc.printf("%d", bit);
    }
    pc.printf("\n");
    for (int i = 0; i < (int)(sizeof(accessories)/sizeof(*accessories)); i++) {
      pc.printf("\nchecking accessory - %s at bit %d\n", accessories[i]->name.c_str(), i);
      int msgState = (msg.data[0] & (1 << accessories[i]->id)) >> accessories[i]->id;
      if (msgState != accessories[i]->currentState) {
        accessories[i]->updateState(msgState);
      }
    }
  }
}