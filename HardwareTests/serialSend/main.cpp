#include "mbed.h"
//#include "platform/mbed_thread.h"

DigitalOut debugPin(PA_8);
DigitalOut led(LED1);
DigitalOut standby(PB_1);
Serial pc(USBTX, USBRX);
CAN can1(PA_11, PA_12);

char send = 0;
int main() {
    pc.printf("Length of message (Bytes): ");
    int msg_len = pc.getc()-48;

    pc.printf("\nSetting message length to %d\n", msg_len);
    can1.frequency(500000);
    led = 0;
    //char msg [4] = {'t','e','s','t'};
    while (true) {
        char send [] = {0};
        for (int byte = 0; byte < msg_len; ++byte){
            for (int bit = 7; bit >=0; bit--) {
                char c = pc.getc()-48;
                send[byte] ^= (-c ^ send[byte]) & (1 << bit);
                pc.printf("%c", c+48);
            }
            pc.printf(" ");
        }
        pc.printf("\nSENT\n");
        if (can1.write(CANMessage(10, send, msg_len))) {
            led = !led;
        }
    }
}