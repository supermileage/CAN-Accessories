// Receives CAN message and turns on the MOSFETS
#include "mbed.h"
//#include "platform/mbed_thread.h"
//#define BLINKING_RATE_MS 1000

// Initialize gate pins
DigitalOut gate1(PB_0);

DigitalOut debugPin(PA_8);
DigitalOut led(LED3); // CAN transmission indicator light
DigitalOut standby(PB_1); // Set board to active mode
CAN can1(PA_11, PA_12); // CAN pins
Ticker flipper;
int triggered = 0;

int main() {

    can1.frequency(500000);
    led = 0;
    standby = 0;
    gate1 = 0;

    CANMessage msg;
    while (true) {
        if (can1.read(msg)) {
            led = !led;
            switch (msg.data[0]) {
            case 0:
              gate1_control();
              break;
        }
        debugPin = !debugPin;
    }
}

void flip_gate1() {
  gate1 = !gate1;
}

void gate1_control() {
  if (!triggered) {
    flipper.attach(&flip_gate1, 500ms);
  } else {
    flipper.detach();
  }
  triggered = !triggered;
}
