// Receives CAN message and turns on the MOSFETS
#include "mbed.h"
//#include "platform/mbed_thread.h"
//#define BLINKING_RATE_MS 1000

// Initialize gate pins

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
            for (int byte = 0; byte < msg.len; ++byte){
                for (int i = 7; i >=0; --i){
                    bool bit = ((msg.data[byte] & 1 << i) >> i) == 1;
                    pc.printf("%d", bit);
                }
                pc.printf(" ");
            }
            pc.printf("\n");
        }
        debugPin = !debugPin;
    }
}