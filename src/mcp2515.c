#include "mcp2515.h"

void mcp2515_init()
{
    mcp2515_reset(); // Recommended as part of powre-on procedure
    mcp2515_bit_modify(CANCTRL_ADDR, 0b11100000, 0b01000000); // Set CAN loopback mode
    mcp2515_bit_modify(CANINTE_ADDR, 0b00000001, 0b00000001);
}

char MCP2515_read_buffer()
{
    char command[2] = {(char) MCP2515_READ_RX_BUFFER, '\0'};
    return spi_transmit_byte(command);
}

void mcp2515_load_buffer(char* data)
{
    int length = sizeof(data)+2; // Command code, address and stop byte
    char command[length];

    command[0] = (char) MCP2515_LOAD_TX_BUFFER;
    for(uint8_t i=1; i<length-1; i++)
    {
        command[i] = data[i-1];
    }
    command[length-1] = '\0';
    
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

void mcp2515_write(char address, char* data)
{   
    int length = sizeof(data)+3; // Command code, address and stop byte
    char command[length];
    command[0] = (char) MCP2515_WRITE;
    command[1] = address;

    for(uint8_t i=2; i<length-1; i++)
    {
        command[i] = data[i-2];
    }

    command[length-1] = '\0';
    spi_transmit_byte(command);
}

void mcp2515_request_to_send()
{
    char command[2] = {(char) MCP2515_REQUEST_TO_SEND, '\0'};
    spi_transmit_byte(&command);
}

char mcp2515_read_status()
{
    char command[2] = {(char) MCP2515_READ_STATUS, '\0'};
    return spi_transmit_byte(&command);
}

void mcp2515_bit_modify(char address, char mask, char data)
{
    char command[5] = {(char) MCP2515_BIT_MODIFY, address, mask, data, '\0'};
    spi_transmit_byte(command);
}

void mcp2515_reset()
{
    char command[2] = {(char) MCP2515_RESET, '\0'};
    spi_transmit_byte(&command);
}