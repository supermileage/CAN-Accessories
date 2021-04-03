#ifndef CANHANDLER_H
#define CANHANDLER_H

class CanHandler {
  public:
    CanHandler();
    void handleMessages();
  private:
    void handleOneHot(CANMessage msg);
    void handleToggle(CANMessage msg);
};


#endif
