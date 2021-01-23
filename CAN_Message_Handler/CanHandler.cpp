#include "mbed.h"
#include "CanItems.h"
#include "pins.h"
#include "CanHandler.h"

CanHandler::CanHandler() {
  can.frequency(500000);
  standby = 0;
  led = 0;

  // Initial Accessory States
  hazards = 0;
  wipers = 0;
  headlights = 0;
  horn = 0;
  breakLights = 0;
  rightInd = 0;
  leftInd = 0;
}

/**
* Reads CAN Bus messages and calls appropriate method to toggle accessory
*/
void CanHandler::handleMessages() {
  CANMessage msg;

  if (can.read(msg)) {
    switch (msg.data[0]) {
      case hazardsID:
        handleHazards();
        break;
      case headlightsID:
        handleHeadlights();
        break;
      case breakLightsID:
        handleBreakLights();
        break;
      case hornID:
        handleHorn();
        break;
      case indicatorsRID:
        handleRightIndicators();
        break;
      case indicatorsLID:
        handleLeftIndicators();
        break;
      case wipersID:
        handleWipers();
        break;
    }
  }
}

/**
* Toggles headlights: switches ON to OFF or vice versa
*/
void CanHandler::handleHeadlights() {
  headlights = !headlights;
}

/**
* Toggles breaklights: switches ON to OFF or vice versa
*/
void CanHandler::handleBreakLights() {
  breakLights = !breakLights;
}

/**
* Toggles horn: switches ON to OFF or vice versa
*/
void CanHandler::handleHorn() {
  horn = !horn;
}

/**
* Toggles wipers: switches ON to OFF or vice versa
*/
void CanHandler::handleWipers() {
  wipers = !wipers;
}

/**
* Hazards blinking
*/
void blinkHazards() {
  hazards = !hazards;
}

/**
* Toggles hazards: switches ON (blinking) to OFF or vice versa
* Sets up recurring interrupt to blink hazards ever 0.5s
*/
void CanHandler::handleHazards() {
  if (hazardsOff) { // Switch from on to off: blinking
    hazardsT.attach(&blinkHazards, 0.5);
  } else {
    hazardsT.detach();
    hazards = 0;
  }
  hazardsOff = !hazardsOff; // switching state
}

/**
* Right indicators blinking
*/
void blinkRightInd() {
  rightInd = !rightInd;
}

/**
* Toggles right indicators: switches ON (blinking) to OFF or vice versa
* Sets up recurring interrupt to blink right indicators ever 0.5s
*/
void CanHandler::handleRightIndicators() {
  if (rightIndOff) { // turn them on blinking
    rightIndT.attach(&blinkRightInd, 0.5);
  } else {
    rightIndT.detach();
    rightInd = 0;
  }
  rightIndOff = !rightIndOff;
}

/**
* Left indicators blinking
*/
void blinkLeftInd() {
  leftInd = !leftInd;
}

/**
* Toggles left indicators: switches ON (blinking) to OFF or vice versa
* Sets up recurring interrupt to blink left indicators ever 0.5s
*/
void CanHandler::handleLeftIndicators() {
  if (leftIndOff) { // turn them on blinking
    leftIndT.attach(&blinkLeftInd, 0.5);
  } else {
    leftIndT.detach();
    leftInd = 0;
  }
}
