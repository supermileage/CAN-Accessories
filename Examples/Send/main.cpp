#include "mbed.h"
//#include "platform/mbed_thread.h"

#define GATE1 PA_2
#define GATE2 PA_7
#define GATE3 PB_7
#define GATE4 PB_6
#define GATE5 PB_5
#define GATE6 PB_4

#define CAN_RX PA_11
#define CAN_TX PA_12
#define CAN_STBY PA_9

DigitalOut debugPin(PA_8);
DigitalOut led(LED3);
DigitalOut standby(CAN_STBY);
CAN can(CAN_RX, CAN_TX);

//char counter = 0;
int main() {
    char counter[]={0, 0xFF};
    can.frequency(500000);
    led = 0;
    standby = 0;
    // char msg [4] = {'t','e','s','t'};
    while (true) {
        counter[1] ^= 0b11111111;  //toggle everything
        
        if (can.write(CANMessage(0x60, counter, 2))) {
            led = !led;
        }
        if (can.tderror()) {
            debugPin = 1;
        }
        else {
            debugPin = 0;
        }
        wait(5);
    }
}