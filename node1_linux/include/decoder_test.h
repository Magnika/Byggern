#ifndef DECODER_TEST_H
#define DECODER_TEST_H

#include "avr.h"
#include "sram.h"
#include <stdlib.h>
#include <stdint.h>
#include <util/delay.h> // Delay functions

/**
 * @brief Set the address pins corresponding to SRAM CS and ADC CS, in turn.
 * 
 */
void test_decoder()
{
    volatile char *ext_ram = (char *) 0x1400;
    ext_ram[1] = rand();
}

#endif // DECODER_TEST_H
