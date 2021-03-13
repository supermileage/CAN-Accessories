# Interfacing with CAN Accessories

Controller Area Network (CAN) Messages sent with a message ID of 10 are received and handled by the CAN Accessories subsystem.

Messages sent to CANACC (CAAC?) (WE NEED A NICE SHORT ACRONYM LOL) (CAN Accessories) consists of 2 or more bytes of data. The first byte (byte 0) contains the operation mode of the message. The remaining bytes (byte 1+) contain operation data as defined by the operation mode. Bytes are little-endian.

(At the time of writing, only operation mode 0 is functional on the CAN-Accessories repository. Other operation modes are being developed.)

Each device managed by CAN Accessories has a corresponding Accessory ID as indicated by the following table:

[CAN Accessory IDs](https://www.notion.so/f77d696999a34ffc8d54b09842da4c63)

## Operation Mode 0: Simple ON/OFF

In operation mode 0, each bit of the operation data is mapped to an Accessory. A bit value of 1 turns on the corresponding output, and a bit value of 0 turns off the output. The bit number corresponds to a device's accessory ID, with the least significant bit of the least significant operation data byte being bit 0.

For example, the a CAN message with data 0x0014 (0b 00000000 00010100) has '1's in bit 2 and 4 of the operation data byte. This will turn on the horn and right indicator if they were not on already, and turn off the rest of the Accessories.

## Operation Mode 1: Toggle Mode (WIP)

Similarly to operation mode 0, in operation mode 1, each bit of the operation data is mapped to an Accessory. In this mode, a bit value of 1 toggles the corresponding, and a bit value of 0 leaves it in its current states. Accessory values are mapped in the same fasion as operation mode 0.

For example, assuming that the horn is currently on and the right indicator is off, a CAN message with data 0x0014 (0b 00000000 00010100) has '1's in bit 2 and 4 of the operation data byte, and will toggle the horn and the right indicator, turning the horn off and the right indicator on.

## Operation Mode 2: Single Device ON/OFF (WIP)
