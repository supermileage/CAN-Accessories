#include "mbed.h"
//#include "platform/mbed_thread.h"

DigitalOut debugPin(PA_8);
DigitalOut led(LED3);
DigitalOut standby(PB_1);
CAN can1(PA_11, PA_12);

char counter = 0;
int main() {
    can1.frequency(500000);
    led = 0;
    standby = 0;
    char msg [4] = {'t','e','s','t'};
    while (true) {
        counter ^= 1 << 0;  //toggle everything
        counter ^= 1 << 1;
        counter ^= 1 << 2;
        if (can1.write(CANMessage(10, &counter, 1))) {
            led = !led;
        }
        if (can1.tderror()) {
            debugPin = 1;
        }
        else {
            debugPin = 0;
        }
        wait(1);
    }
}