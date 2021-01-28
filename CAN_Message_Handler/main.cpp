#include "mbed.h"
//#include "platform/mbed_thread.h"
#include "CanHandler.h"

CanHandler canHandler;

int main()
{
    while (true) {
        canHandler.handleMessages();
    }
}
