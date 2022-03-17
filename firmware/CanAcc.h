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

#define ACCESSORIES_ID 0x80

#define STATUS_PERIOD 1.0     // time in seconds between sending status updates

/*
* Accessory definitions
* ID: id of accessory
* Board: Board that accessory is attached to -
*   1 - Front board
*   2 - Rear board
*   3 - Both boards
* Blinks: Whether accessory blinks
* Gates: gates that accessory is attached to
*/
#define HEADLIGHTS_ID               0
#define HEADLIGHTS_BOARD            1               // Front Board
#define HEADLIGHTS_NAME             "Headlights"
#define HEADLIGHTS_BLINKS           0
#define HEADLIGHTS_GATES            0b00000010      // GATE2

#define BRAKELIGHTS_ID              1
#define BRAKELIGHTS_BOARD           2               // Rear Board
#define BRAKELIGHTS_NAME            "Brakelights"
#define BRAKELIGHTS_BLINKS          0
#define BRAKELIGHTS_GATES           0b00000100      // GATE3

#define HORN_ID                     2
#define HORN_BOARD                  1               // Front Board
#define HORN_NAME                   "Horn"
#define HORN_BLINKS                 0
#define HORN_GATEs                  0b00001000      // GATE4

#define HAZARDS_ID                  3
#define HAZARDS_BOARD               3               // Both Boards
#define HAZARDS_NAME                "Hazards"
#define HAZARDS_BLINKS              1
#define HAZARDS_GATES               0b00110000      // GATE5, GATE6

#define RIGHT_INDICATORS_ID         4
#define RIGHT_INDICATORS_BOARD      3               // Both Boards
#define RIGHT_INDICATORS_NAME       "Right Indicators"
#define RIGHT_INDICATORS_BLINKS     1
#define RIGHT_INDICATORS_GATES      0b00010000      // GATE5

#define LEFT_INDICATORS_ID          5
#define LEFT_INDICATORS_BOARD       3               // Both Boards
#define LEFT_INDICATORS_NAME        "Left Indicators"
#define LEFT_INDICATORS_BLINKS      1
#define LEFT_INDICATORS_GATES       0b00100000      // GATE6


#define WIPERS_ID                   6
#define WIPERS_BOARD                1               // Front Board
#define WIPERS_NAME                 "Wipers"
#define WIPERS_BLINKS               0
#define WIPERS_GATES                0b00000100      // GATE3

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