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
Serial pc(USBTX, USBRX);

int main() {

    can1.frequency(500000);
    led = 0;
    standby = 0;
    CANMessage msg;
    while (true) {
        if (can1.read(msg)) {
            led = !led;
            pc.printf("%d  -  ", msg.data[0]);
            for (int i = 7; i >=0; --i){
                bool bit = ((msg.data[0] & 1 << i) >> i) == 1;
                pc.printf("%d", bit);
                switch(i) {
                    case 0:
                        gate1 = bit;
                        break;
                    case 1:
                        gate2 = bit;
                        break;
                    case 2:
                        gate3 = bit;
                        break;
                    default:
                        break;
                }
            }
            pc.printf("\n");
        }
        debugPin = !debugPin;
    }
}