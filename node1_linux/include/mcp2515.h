#ifndef MCP2515_H
#define MCP2515_H

#include "spi.h"
#include <util/delay.h> // Delay functions

#define F_OSC 16000000 // Oscillation frequency


// Instruction set
#define MCP2515_RESET 0b11000000
#define MCP2515_READ 0b00000011
#define MCP2515_WRITE 0b00000010
#define MCP2515_READ_STATUS 0b10100000
#define MCP2515_REQUEST_TO_SEND 0x81 // define the last 3 bits to choose what register to publish
#define MCP2515_BIT_MODIFY 0b00000101
#define MCP2515_LOAD_TX_BUFFER 0b01000000 // Load TX buffer 0, Start at TXB0SIDH
#define MCP2515_READ_RX_BUFFER 0b10010000 // Receive Buffer 0, Start at RXB0SIDH

// Address map
#define CNF1_ADDR 0x2a
#define CNF2_ADDR 0x29
#define CNF3_ADDR 0x28

#define CANCTRL_ADDR 0x0F
#define CANINTE_ADDR 0x2B
#define CANINTF_ADDR 0x2C

#define TXB0CTRL_ADDR 0x30
#define TXB0SIDH_ADDR 0x31
#define TXB0SIDL_ADDR 0x32
#define TXB0EID8_ADDR 0x33
#define TXB0EID0_ADDR 0x34
#define TXB0DLC_ADDR 0x35
#define TXB0D0_ADDR 0x36

#define RXB0CTRL_ADDR 0x60
#define RXB0SIDH_ADDR 0x61
#define RXB0SIDL_ADDR 0x62
#define RXB0EID8_ADDR 0x63
#define RXB0EID0_ADDR 0x64
#define RXB0DLC_ADDR 0x65
#define RXB0D0_ADDR 0x66

// Commands
#define MCP2515_MODE_NORMAL 0x00
#define MCP2515_MODE_LOOPBACK 0x40
#define MCP2512_MODE_MASK 0b11100000

// We want to achieve a CAN baud rate of 250 kHz.
// Followin the example in the datasheet:
// T_osc = 62.5 ns
// We achieve an integer TQ by setting BRP=2, yielding TQ=250ns
// BR = 1/t_bit = 1/(cumulative sum of TQ's).
// To achieve our desired baud, we need the bit time to be 16 TQ.
// SyncSeg=1TQ and PropSeg=2TQ. We set PS1=6TQ. This limits PS2 to 8 TQ.
// PS2 = 7TQ. This limits SJW to 6 TQ.
// We set SJW to its max. value of 4.
// The total bit time is then 7+6+2+1=16TQ.
#define TQ_PROP_SEG 2
#define TQ_SYNC_SEG 1
#define TQ_PS1 6
#define TQ_PS2 7
#define N_TQ 16 // Number of time quantas in 1 bit time
#define TQ_SJW (0b11 << 6) // Sync jump width
#define BRP 2 // NOTE: not the same as the baud rate bits! See MCP2515 datasheet.
#define BTLMODE 0x80 // Length of PS2 determined by PHSEG22:PHSEG20 bits of CNF3
#define SAM 0x40 // Sample 3x at sample point, why not
#define PHSEG1 (0x30) // TQ_PS1-1
#define PRSEG 0x1 // TQ_PROG_SEG-1

#define WAKFIL_ENABLED 0x40 // Wake-up filter enable
#define WAKFIL_DISABLED 0x00 // Wake-up filter disable
#define PHSEG2 (TQ_PS2-1) // See datasheet p.45

char MCP2515_read_buffer();

void mcp2515_load_buffer(char* data);

void mcp2515_CAN_publish(char data);

void mcp2515_init();

char mcp2515_read(char address);

void mcp2515_write(char address, char data);

void mcp2515_request_to_send();

char mcp2515_read_status();

void mcp2515_bit_modify(char address, char mask, char data);

void mcp2515_reset();

#endif // MCP2515