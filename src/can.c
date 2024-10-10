#include "can.h"

void can_init()
{
    mcp2515_init();
}

void can_transmit(const can_frame_t* msg)
{
    mcp2515_bit_modify(CANINTE_ADDR, 0b00000100, 0x00);

    char frame[13];
    frame[0] = msg->SIDH;
    frame[1] = msg->SIDL;
    frame[2] = msg->EID8;
    frame[3] = msg->EID0;
    frame[4] = msg->DLC;

    for(uint8_t i=0; i<8; i++)
    {
        frame[i+5] = msg->data[i];
    }

    mcp2515_load_buffer(frame);
}

can_frame_t can_read()
{
    can_frame_t msg_received;
    msg_received.SIDH = mcp2515_read(RXB0SIDH_ADDR);
    msg_received.SIDL = mcp2515_read(RXB0SIDH_ADDR+1);
    msg_received.EID8 = mcp2515_read(RXB0SIDH_ADDR+2);
    msg_received.EID0 = mcp2515_read(RXB0SIDH_ADDR+3);
    msg_received.DLC = mcp2515_read(RXB0SIDH_ADDR+4);

    for(uint8_t i=0; i<8; i++)
    {
        msg_received.data[i] = mcp2515_read(RXB0SIDH_ADDR+5+i);
    }
    
    return msg_received;
}