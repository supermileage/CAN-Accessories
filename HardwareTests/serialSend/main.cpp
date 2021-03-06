#include "mbed.h"
//#include "platform/mbed_thread.h"

DigitalOut debugPin(PA_8);
DigitalOut led(LED3);
DigitalOut standby(PB_1);
Serial pc(USBTX, USBRX);
CAN can1(PA_11, PA_12);

char send = 0;
int main() {
    can1.frequency(500000);
    led = 0;
    char msg [4] = {'t','e','s','t'};
    while (true) {
        send = 0;
        for (int bit = 7; bit >=0; bit--) {
            char c = pc.getc();
            if (c == '1'){
                send ^= 1 << bit;
            }
            pc.printf("%c", c);
        }
        pc.printf("\nSENT\n");
        if (can1.write(CANMessage(10, &send, 1))) {
            led = !led;
        }

    }
}