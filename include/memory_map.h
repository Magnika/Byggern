#ifndef MEMORY_MAP_H
#define MEMORY_MAP_H

#include <stdint.h>

#define MEM_MAP ((ATMega_memory_map_t*) 0x1000) // memory map base address

typedef struct
{
    volatile uint8_t OLED_COMMAND[512];
    volatile uint8_t OLED_DATA[512];
    volatile uint8_t ADC[1024];
    volatile uint8_t SRAM[2048];
} ATMega_memory_map_t;


#endif // MEMORY_MAP_H