// Receives CAN message and turns on the MOSFETS
#include "mbed.h"
//#include "platform/mbed_thread.h"
//#define BLINKING_RATE_MS 1000

#define GATE1 PA_2
#define GATE2 PA_7
#define GATE3 PB_7
#define GATE4 PB_6
#define GATE5 PB_5
#define GATE6 PB_4

#define CAN_RX PA_11
#define CAN_TX PA_12
#define CAN_STBY PA_9

// Initialize gate pins
DigitalOut gate1(GATE1);
DigitalOut gate2(GATE2);
DigitalOut gate3(GATE3);
DigitalOut gate4(GATE4);
DigitalOut gate5(GATE5);
DigitalOut gate6(GATE6);


DigitalOut debugPin(PA_8);
DigitalOut led(LED3); // CAN transmission indicator light
DigitalOut standby(CAN_STBY); // Set board to active mode
CAN can(CAN_RX, CAN_TX); // CAN pins

int main() {

    DigitalOut gates[] = {gate1, gate2, gate3, gate4, gate5, gate6};
    can.frequency(500000);
    led = 0;
    standby = 0;
    CANMessage msg;
    while (true) {
        if (can.read(msg)) {
            led = !led;
            for (int i = 0; i < 6; ++i) {
                gates[i] = (msg.data[0] & 1 << i) >> i;
            }
            
        }
        debugPin = !debugPin;
    }
}