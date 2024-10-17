#ifndef MCP2515_H
#define MCP2515_H

#include "spi.h"
#include <util/delay.h> // Delay functions


// Instruction set
#define MCP2515_RESET 0b11000000
#define MCP2515_READ 0b00000011
#define MCP2515_WRITE 0b00000010
#define MCP2515_READ_STATUS 0b10100000
#define MCP2515_REQUEST_TO_SEND 0b10000001 // define the last 3 bits to choose what register to publish
#define MCP2515_BIT_MODIFY 0b00000101
#define MCP2515_LOAD_TX_BUFFER 0b01000000 // Load TX buffer 0, Start at TXB0SIDH
#define MCP2515_READ_RX_BUFFER 0b10010000 // Receive Buffer 0, Start at RXB0SIDH

#define CANCTRL_ADDR 0x0F
#define CANINTE_ADDR 0b00101011

#define TBX0CTRL_ADDR 0b00110000

#define RXB0CTRL_ADDR 0b01100000
#define RXB0SIDH_ADDR 0b01100001

char MCP2515_read_buffer();

void mcp2515_load_buffer(char* data);

void mcp2515_CAN_publish(char data);

void mcp2515_init();

char mcp2515_read(char address);

void mcp2515_write(char address, char* data);

void mcp2515_request_to_send();

char mcp2515_read_status();

void mcp2515_bit_modify(char address, char mask, char data);

void mcp2515_reset();

#endif // MCP2515