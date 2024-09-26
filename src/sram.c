#include "sram.h"

void SRAM_init()
{
    SRE_bit_enable();
    AD70_pullup_activate();
    SFIOR = (0<<XMM1) | (0<<XMM0) | (1<<XMM2);
}

void SRE_bit_enable()
{
    MCUCR = (1<<SRE);
}

void AD70_pullup_activate()
{
    PORTA = (1<<PA0) | (1<<PA1) | (1<<PA2) | (1<<PA3) | (1<<PA4) | (1<<PA5) | (1<<PA6) | (1<<PA7);
}

void sram_write(uint8_t* addr, uint8_t value)
{
    *addr = value;
}

uint8_t sram_read(uint8_t* addr)
{
    return *addr;
}