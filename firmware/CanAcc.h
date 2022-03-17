#ifndef CANACC_H
#define CANACC_H

#include "mbed.h"

// Gate connections
#define GATE1       PA_2      // Disables USB Serial
#define GATE2       PA_7
#define GATE3       PB_7
#define GATE4       PB_6
#define GATE5       PB_5
#define GATE6       PB_4

#define ACCESSORIES_CAN_ID 0x60

#define STATUS_PERIOD 1.0     // time in seconds between sending status updates

namespace CanAcc
{
    struct AccInfo{
        int id;
        int board;
        char name[32];
        bool initial_state;
        bool blinks;
        unsigned int gate;
    };

    // TODO: convert these into the macros
    /* 
     * {id, boards, name, blinks, gates}
     * id: Included in CAN message to identify accessory
     * boards: one-hot encoded value to determine which boards house the
     *         accessory
     * name: name of the accessory - used for serial output
     * blinks: whether the accesory blinks.
     * gates - index of gate in gates[] which accessory is attached to
     */
    constexpr AccInfo acc_info_list[] = {
        // {id, boards, name, blinks, gates}
        {0, 0b11, "Headlights / Running lights", 0, false, 1},
        {1, 0b10, "Brakelights", 0, false, 2},
        {2, 0b01, "Horn", 0, false, 3},
        {4, 0b11, "Right Indicators", 1, true, 4},
        {5, 0b11, "Left Indicators", 1, true, 5},
        {6, 0b01, "Wipers", 0, false, 2}
    };

    constexpr PinName gates[] = {
        PA_2,
        PA_7,
        PB_7,
        PB_6,
        PB_5,
        PB_4
    };
}

// CAN connections
#define CAN_RX      PA_11
#define CAN_TX      PA_12
#define CAN_STBY    PA_9

// Board Select Solder Bridge Connections
#define BOARD_SEL_0 PA_0
#define BOARD_SEL_1 PA_1
#define BOARD_SEL_2 PA_3        // Disables USB Serial

// Blinkrate for blinking accessories:
#define BLINK_RATE  0.5

// Misc
#define LED         LED3

#endif