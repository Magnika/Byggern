#include "can.h"

void can_init()
{
    mcp2515_init();
}

void can_transmit(const can_frame_t* msg)
{
    mcp2515_bit_modify(CANINTE_ADDR, 0b00000100, 0x00);

    char frame_header[13];
    frame_header[0] = msg->SIDH;
    frame_header[1] = msg->SIDL;
    frame_header[2] = msg->EID8;
    frame_header[3] = msg->EID0;
    frame_header[4] = msg->DLC;

    for(uint8_t i=0; i<8; i++)
    {
        frame_header[i+5] = msg->data[i];
    }

    mcp2515_load_buffer(frame_header);
}

void can_read();