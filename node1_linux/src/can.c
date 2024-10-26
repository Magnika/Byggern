#include "can_node1.h"

void can_init()
{
    mcp2515_init();
    mcp2515_bit_modify(CANCTRL_ADDR, MCP2512_MODE_MASK, MCP2515_MODE_NORMAL); // Set CAN controller mode
}

void can_transmit(can_frame_t* msg)
{
    //mcp2515_bit_modify(CANINTE_ADDR, 0b00000100, 0x00);

    mcp2515_write(TXB0SIDH_ADDR, msg->id >> 3); // SID>10:3> resides in the SIDH register, p.19.
    mcp2515_write(TXB0SIDL_ADDR, msg->id % 8 << 5); // Extract the bottom 3 bits from id (modulo 8 operation gives the bits 3:0, modulo 16 gives 4:0 etc..). Then left-shift to place at correct spot in register.
    mcp2515_write(TXB0DLC_ADDR, msg->data_length);

    // Loop write data bytes
    for(uint8_t i=0; i<msg->data_length; i++)
    {
        mcp2515_write(TXB0D0_ADDR+i, msg->data[i]);
    }

    // Send can frame
    mcp2515_request_to_send();
}

void can_read(can_frame_t* msg)
{
    uint8_t id_high_bits = mcp2515_read(RXB0SIDH_ADDR);
    uint8_t id_low_bits = mcp2515_read(RXB0SIDL_ADDR);
    msg->id = (id_low_bits >> 5) + (id_high_bits << 3); // Inverse of transmit function

    msg->data_length = mcp2515_read(RXB0DLC_ADDR);

    for(int i=0; i<msg->data_length; i++)
    {
        msg->data[i] = mcp2515_read(RXB0D0_ADDR+i);
    }

    printf("id high = %d\n\r", id_high_bits);
    printf("data[0] = %c\n\r", msg->data[0]);
}