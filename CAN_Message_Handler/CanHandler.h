#ifndef CANHANDLER_H
#define CANHANDLER_H

class CanHandler {
  public:
    CanHandler();
    void handleMessages();
  private:
    void handleHazards();
    void handleHeadlights();
    void handleBreakLights();
    void handleHorn();
    void handleRightIndicators();
    void handleLeftIndicators();
    void handleWipers();
};

#endif
