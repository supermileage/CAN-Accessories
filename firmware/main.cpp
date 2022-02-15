#include "mbed.h"
#include "CanAcc.h"
#include "Accessory.h"
#include <vector>

int main( void ) {
    // setup IO
    DigitalOut led(LED);

    // setup Serial
    Serial pc(USBTX, USBRX);
    pc.baud(115200);
    
    // pretty
    pc.printf(
    "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\r\n"
    " dP\"\"b8    db    88b 88                                                       \r\n"
    "dP   `\"   dPYb   88Yb88                                                       \r\n"
    "Yb       dP__Yb  88 Y88                                                       \r\n"
    " YboodP dP\"\"\"\"Yb 88  Y8                                                       \r\n"
    "   db     dP\"\"b8  dP\"\"b8 888888 .dP\"Y8 .dP\"Y8  dP\"Yb  88\"\"Yb 88 888888 .dP\"Y8 \r\n"
    "  dPYb   dP   `\" dP   `\" 88__   `Ybo.\" `Ybo.\" dP   Yb 88__dP 88 88__   `Ybo.\" \r\n"
    " dP__Yb  Yb      Yb      88\"\"   o.`Y8b o.`Y8b Yb   dP 88\"Yb  88 88\"\"   o.`Y8b \r\n"
    "dP\"\"\"\"Yb  YboodP  YboodP 888888 8bodP' 8bodP'  YbodP  88  Yb 88 888888 8bodP' \r\n"
    "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\r\n"
    );
    
    // Setup CAN
    pc.printf("Setting up CAN..");
    CAN can(CAN_RX, CAN_TX);
    DigitalOut can_stdby(CAN_STBY);
    can.frequency(500000);
    can_stdby = 0;
    pc.printf(" Set up CAN\r\n");

    // TODO: make this real
    int board = 1;

    std::vector<Accessory *> accessories;

    for (
        unsigned int i = 0;
        i < sizeof(CanAcc::acc_info_list)/sizeof(CanAcc::acc_info_list[0]);
        ++i
    ){
        // check if accessory belongs on this board
        if (CanAcc::acc_info_list[i].board & board){
            // add to accessory list
            pc.printf("Adding %s to accessory list\r\n", CanAcc::acc_info_list[i].name);
            accessories.push_back(new Accessory(
                CanAcc::gates[CanAcc::acc_info_list[i].gate],
                CanAcc::acc_info_list[i].initial_state,
                CanAcc::acc_info_list[i].blinks,
                CanAcc::acc_info_list[i].id,
                CanAcc::acc_info_list[i].board,
                CanAcc::acc_info_list[i].name
            ));
        }
    }



    // gates
    CANMessage msg;
    while (true) {
        if (can.read(msg)) {
            /*
            * Switch for CANACC Operation Modes:
            * 0: Simple ON/OFF
            * 1: Toggle Mode
            * 2: Accessory ON/OFF
            */

           pc.printf(
               "---------\r\nmessage received: 0x");
           for(int i = 0; i < msg.len; ++i) {
               printf("%02x ",msg.data[i]);
           }
           printf("\r\n");

            switch(msg.data[0]){
                // Simple ON/OFF - Byte 1 represents state of all accessories
                case 0:
                    pc.printf("Operation mode: 0 - Simple ON/OFF\r\n");
                    led = !led;
                    for (int i = 0; i < 8; ++i) {
                        bool on = (msg.data[1] & (1 << i)) >> i;
                        // find accessory
                        for (Accessory *accessory : accessories) {
                            if (accessory->id == i) {
                                pc.printf("Turning %s %s", accessory->name, on ? "on" : "off");
                                accessory->updateState(on);
                            }
                        }
                    }
                break;

                // Toggle mode - Byte 1 represents accessories to toggle
                case 1:
                    pc.printf("Operation mode: 1 - Toggle mode\r\n");
                break;

                // Accessory ON/OFF - Each byte after byte 0 - [7 bits ACC ID][1 bit on/off]
                case 2:
                    // TODO: implement this
                    pc.printf("Operation mode: 2 - Individual ON/OFF\r\n");
                break;
                default:
                    pc.printf("Received Invalid Command\r\n");
                break;
            }
            

        }
    }
}