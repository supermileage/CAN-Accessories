
#include "LedTicker.h"
Serial pc(USBTX, USBRX);

//class LedTicker {
//    public:
//        DigitalOut accessory;
//        LedTicker(PinName pin) : accessory(pin){
//           accessory = 0;
//        }
//        void start(){
//            t.attach(callback(this, &LedTicker::toggle_acc), 0.5);
//        }
//        void toggle_acc(){
//            accessory = !accessory;
//        }
//    private:
//        Ticker t;
//    
//};

int main() {
    // Init the ticker with the address of the function (toggle_led) to be attached and the interval (100 ms)
    pc.printf("stuff");
    LedTicker tick(LED1);
    LedTicker tick1(LED1);
    tick.start();
    wait(0.25);
    tick1.start();
    while(true){
    
    }
    
}