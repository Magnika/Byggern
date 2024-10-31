#include "mcp2515.h"

void mcp2515_init()
{
    mcp2515_reset(); // Recommended as part of powre-on procedure
    _delay_ms(200);

    /* CAN bit timing */
    mcp2515_write(CNF1_ADDR, (SJW << SJW_OFFSET) | BRP);
    mcp2515_write(CNF2_ADDR, (BTLMODE << BTLMODE_OFFSET) | (SAM << SAM_OFFSET) | (PHSEG1 << PHSEG1_OFFSET) | (PRSEG << PRSEG_OFFSET));
    mcp2515_write(CNF3_ADDR, (WAKFIL_ENABLE << WAKFIL_OFFSET) | (PHSEG2 << PHSEG2_OFFSET));

    mcp2515_bit_modify(CANINTE_ADDR, 0b00000001, 0b00000001); // Configure interrupt
}

char MCP2515_read_buffer()
{
    char message;
    char command = (char) MCP2515_READ_RX_BUFFER;
    spi_transmit_bytes(&command, 1, 1, &message);
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
    
    spi_transmit_bytes(command, length, 0, NULL);
}

void mcp2515_CAN_publish(char data)
{
    mcp2515_load_buffer(data);
    mcp2515_request_to_send();
}

char mcp2515_read(char address)
{
    char message;
    unset_CS();
    spi_transmit_byte(MCP2515_READ);
    spi_transmit_byte(address);
    message = spi_read();
    set_CS();

    return message;
}

void mcp2515_write(char address, char data)
{   
    unset_CS();
    spi_transmit_byte(MCP2515_WRITE);
    spi_transmit_byte(address);
    spi_transmit_byte(data);
    set_CS();
}

void mcp2515_request_to_send()
{
    unset_CS();
    spi_transmit_byte(MCP2515_REQUEST_TO_SEND);
    set_CS();
}

char mcp2515_read_status()
{   
    unset_CS();
    spi_transmit_byte(MCP2515_READ_STATUS);
    char status = spi_read();
    set_CS();

    return status;
}

void mcp2515_bit_modify(char address, char mask, char data)
{
    unset_CS();
    spi_transmit_byte(MCP2515_BIT_MODIFY);
    spi_transmit_byte(address);
    spi_transmit_byte(mask);
    spi_transmit_byte(data);
    set_CS();
}

void mcp2515_reset()
{
    unset_CS();
    spi_transmit_byte(MCP2515_RESET);
    set_CS();
}

