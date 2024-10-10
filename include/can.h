#ifndef CAN_H
#define CAN_H

#include "mcp2515.h"

typedef struct
{
    uint8_t sof : 1;         // Start of Frame (1 bit)
    
    uint16_t id : 11;        // 11-bit Identifier
    uint8_t rtr : 1;         // Remote Transmission Request (1 bit)

    uint8_t ide : 1;         // Identifier Extension (IDE), must be 0 for standard frame
    uint8_t rb0 : 1;         // Reserved Bit Zero (RB0), must be 0
    uint8_t dlc : 4;         // Data Length Code (DLC), 0-8 bytes
    
    uint8_t data[8];         // Data field (up to 8 bytes of data, depends on DLC)
    
    uint16_t crc : 15;       // 15-bit CRC sequence
    uint8_t crc_delim : 1;   // CRC Delimiter (1 bit)
    
    uint8_t ack_slot : 1;    // ACK Slot (1 bit)
    uint8_t ack_delim : 1;   // ACK Delimiter (1 bit)
} can_frame_t;


void can_init();

void can_transmit();

void can_read();

#endif // CAN_H