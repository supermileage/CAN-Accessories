#include "mbed.h"
#include "CanHandler.h"
#include "Accessory.h"

#define CAN_ID 0x00A

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
  can.filter(CAN_ID, 0xFFF, CANStandard, 0); //Set CAN filter to only allow IDs of 0x00A, or 10. ID is 11 bits, thus 0x7FF masks all bits.
}

/**
* Reads CAN Bus messages and toggles accessories if its state has changed.
*/
void CanHandler::handleMessages() {
  CANMessage msg;
  if (can.read(msg)) {
    //prints first byte of message in binary form
    pc.printf("\n###########################################################\n");
    pc.printf("Message received: ");
    // print out data bytes for debug
    for (int b = 0; b < msg.len; ++b) {
      for (int i = 7; i >=0; --i){
        bool bit = ((msg.data[b] & 1 << i) >> i) == 1;
        pc.printf("%d", bit);
      }
      pc.printf(" ");
    }
    pc.printf("\n");
    switch(msg.data[0]){
      case 0:
        pc.printf("Operation mode 0 - one-hot");
        handleOneHot(msg);
        break;
      case 1:
        pc.printf("Operation mode 1 - toggle");
        handleToggle(msg);
        break;
      case 2:
        pc.printf("Operation mode 2 - switch - ID");
        //stuff here
        break;
      default:
        pc.printf("invalid operation mode, defaulting to one-hot");
        handleOneHot(msg);
        break;
    }

    
  }
}

void CanHandler::handleOneHot(CANMessage msg) {
  int b = 1;
  int bit = 0;
  printf("\n");
  for (int i = 0; i < (int)(sizeof(accessories)/sizeof(*accessories)) && b < msg.len; i++) {
      pc.printf("checking accessory - %s at bit %d\n", accessories[i]->name.c_str(), accessories[i]->id); // dont know why but id is not printing.
      int msgState = (msg.data[b] & (1 << accessories[i]->id)) >> accessories[i]->id;
      if (msgState != accessories[i]->currentState) {
        accessories[i]->updateState(msgState);
      }
      ++bit;
      if (bit >= 8){
        ++b;
        bit = 0;
      }
    }
}

void CanHandler::handleToggle(CANMessage msg) {
  int b = 1;
  int bit = 0;
  printf("\n");
  for (int i = 0; i < (int)(sizeof(accessories)/sizeof(*accessories)) && b < msg.len; i++) {
      int msgState = (msg.data[b] & (1 << accessories[i]->id)) >> accessories[i]->id;
      if (msgState) {
        pc.printf("toggling accessory - %s\n", accessories[i]->name.c_str());
        accessories[i]->updateState(!accessories[i]->currentState);
      }
      ++bit;
      if (bit >= 8){
        ++b;
        bit = 0;
      }
    }
}