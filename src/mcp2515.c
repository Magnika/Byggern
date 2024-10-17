#include "mcp2515.h"

void mcp2515_init()
{
    mcp2515_reset(); // Recommended as part of powre-on procedure
    _delay_us(100);
    mcp2515_bit_modify(CANCTRL_ADDR, 0b11100000, 0b01000000); // Set CAN loopback mode
    mcp2515_bit_modify(CANINTE_ADDR, 0b00000001, 0b00000001);
}

char MCP2515_read_buffer()
{
    char message;
    char command = (char) MCP2515_READ_RX_BUFFER;
    spi_transmit_byte(&command, 1, 1, &message);
    return message;
}

void mcp2515_load_buffer(char* data)
{
    int length = 14; // Command code, data
    char command[length];

    command[0] = (char) MCP2515_LOAD_TX_BUFFER;
    for(uint8_t i=1; i<length-1; i++)
    {
        command[i] = data[i-1];
    }
    
    spi_transmit_byte(command, length, 0, NULL);
}

void mcp2515_CAN_publish(char data)
{
    mcp2515_load_buffer(data);
    mcp2515_request_to_send();
}

char mcp2515_read(char address)
{
    char message;
    char c[2] = {(char)MCP2515_READ, address};
    spi_transmit_byte(c, 2,1, &message);
    return message;
}

void mcp2515_write(char address, char* data)
{   
    int length = sizeof(data)+2; // Command code, address and stop byte
    char command[length];
    command[0] = (char) MCP2515_WRITE;
    command[1] = address;

    for(uint8_t i=2; i<length-1; i++)
    {
        command[i] = data[i-2];
    }
    spi_transmit_byte(command, length, 0, NULL);
}

void mcp2515_request_to_send()
{
    char command = (char) MCP2515_REQUEST_TO_SEND;
    spi_transmit_byte(&command, 1, 0, NULL);
}

char mcp2515_read_status()
{
    char message;
    char command = (char) MCP2515_READ_STATUS;
    spi_transmit_byte(&command, 1, 1, &message);
    return message;
}

void mcp2515_bit_modify(char address, char mask, char data)
{
    char command[4] = {(char) MCP2515_BIT_MODIFY, address, mask, data};
    spi_transmit_byte(command, 4, 0, NULL);
}

void mcp2515_reset()
{
    char command = (char) MCP2515_RESET;
    spi_transmit_byte(&command, 1, 0, NULL);
}