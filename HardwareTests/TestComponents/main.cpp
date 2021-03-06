// Receives CAN message and turns on the MOSFETS
#include "mbed.h"
//#include "platform/mbed_thread.h"
//#define BLINKING_RATE_MS 1000

// Initialize gate pins
DigitalOut gate1(PB_0);
DigitalOut gate2(PB_7);
DigitalOut gate3(PB_6);

DigitalOut debugPin(PA_8);
DigitalOut led(LED3); // CAN transmission indicator light
DigitalOut standby(PB_1); // Set board to active mode
CAN can1(PA_11, PA_12); // CAN pins

int main() {

    can1.frequency(500000);
    led = 0;
    standby = 0;
    gate1 = 0;
    gate2 = 0;
    gate3 = 0;
    while (true) {
        gate1 = !gate1;
        gate2 = !gate2;
        gate3 = !gate3;
        led = !led;
        wait(1);
    }
}