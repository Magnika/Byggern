#include "mcp2515.h"

void mcp2515_init()
{
    mcp2515_reset(); // Recommended as part of powre-on procedure
    mcp2515_bit_modify(CANCTRL_ADDR, 0b11100000, 0b01000000); // Set CAN loopback mode
}

char MCP2515_read_buffer()
{
    char commad[2] = {(char) MCP2515_READ_RX_BUFFER, '\0'};
    return spi_transmit_byte(commad);
}

void mcp2515_load_buffer(char data)
{
    char command[3] = {(char) MCP2515_LOAD_TX_BUFFER, data, '\0'};
    spi_transmit_byte(command);
}

void mcp2515_CAN_publish(char data)
{
    mcp2515_load_buffer(data);
    mcp2515_request_to_send();
}

char mcp2515_read(char address)
{
    char c[3] = {(char)MCP2515_READ, address, '\0'};
    return spi_transmit_byte(c);
}

void mcp2515_write(char address, char data)
{
    char command[4] = {(char) MCP2515_WRITE, address, data, '\0'};
    spi_transmit_byte(command);
}

void mcp2515_request_to_send()
{
    spi_transmit_byte((char) MCP2515_REQUEST_TO_SEND);
}

char mcp2515_read_status()
{
    return spi_transmit_byte((char) MCP2515_READ_STATUS);
}

void mcp2515_bit_modify(char address, char mask, char data)
{
    char command[5] = {(char) MCP2515_BIT_MODIFY, address, mask, data, '\0'};
    spi_transmit_byte(command);
}

void mcp2515_reset()
{
    spi_transmit_byte((char) MCP2515_RESET);
}