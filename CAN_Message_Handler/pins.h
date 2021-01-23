// setup output pins
DigitalOut hazards(PB_0); // need to add correct pinouts
DigitalOut wipers(PB_0);
DigitalOut headlights(PB_0);
DigitalOut horn(PB_0);
DigitalOut breakLights(PB_0);
DigitalOut rightInd(PB_0);
DigitalOut leftInd(PB_0);

// CAN pins
CAN can(PA_11, PA_12);
DigitalOut standby(PB_1);
DigitalOut debugPin(PA_8);
DigitalOut led(LED3); // for debugging

// Tickers: recurring interrupts to control blinking accessories
Ticker hazardsT;
Ticker rightIndT;
Ticker leftIndT;

// Indicators for blinking accessiories
int hazardsOff = 1;
int rightIndOff = 1;
int leftIndOff = 1;
