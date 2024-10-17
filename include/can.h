#ifndef CAN_H
#define CAN_H

#include "mcp2515.h"

typedef struct
{
    uint8_t SIDH;         // Standard identifier high byte
    uint8_t SIDL;         // Standard identifier low byte. Also contains EXIDE at bit 3 and EID[17:16] at bits[1:0]
    uint8_t EID8;         // Extended identifier high byte
    uint8_t EID0;         // Extended identifier high byte
    uint8_t DLC;          // Data Length Code (0-8), also contains RTR at bit 6
    
    char data[8];         // Data field (up to 8 bytes of data, depends on DLC)
} can_frame_t;


void can_init();

void can_transmit(const can_frame_t* msg);

can_frame_t can_read();

#endif // CAN_H