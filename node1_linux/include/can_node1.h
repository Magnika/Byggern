#ifndef CAN_H
#define CAN_H

#include "mcp2515.h"

typedef struct
{
    uint16_t id;
    char data_length;
    char data[8];
} can_frame_t;

void can_init();

void can_transmit(can_frame_t* msg);

void can_read(can_frame_t* msg);

#endif // CAN_H