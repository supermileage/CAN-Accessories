#include "mbed.h"
//#include "platform/mbed_thread.h"
#include "CanHandler.h"
DigitalOut standby(PB_1); // Set board to active mode




int main()
{
    Serial pc(USBTX, USBRX);
    
    CanHandler canHandler;
    pc.printf("Setting CAN transceiver to active mode\n");

    //active pin is active low - this sets transceiver to active mode.
    standby = 0;

    pc.printf(
        "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
        " dP\"\"b8    db    88b 88                                                       \n"
        "dP   `\"   dPYb   88Yb88                                                       \n"
        "Yb       dP__Yb  88 Y88                                                       \n"
        " YboodP dP\"\"\"\"Yb 88  Y8                                                       \n"
        "   db     dP\"\"b8  dP\"\"b8 888888 .dP\"Y8 .dP\"Y8  dP\"Yb  88\"\"Yb 88 888888 .dP\"Y8 \n"
        "  dPYb   dP   `\" dP   `\" 88__   `Ybo.\" `Ybo.\" dP   Yb 88__dP 88 88__   `Ybo.\" \n"
        " dP__Yb  Yb      Yb      88\"\"   o.`Y8b o.`Y8b Yb   dP 88\"Yb  88 88\"\"   o.`Y8b \n"
        "dP\"\"\"\"Yb  YboodP  YboodP 888888 8bodP' 8bodP'  YbodP  88  Yb 88 888888 8bodP' \n"
        "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
    ); //I needed a break from MBED's random restrictions and debugging, so you get this lovely ASCII art included free of charge!
    pc.printf("Welcome to CAN-Accessory's SPAGHETTI CODE OF HELL!~\n");

    while (true) {
        canHandler.handleMessages();
    }
}
