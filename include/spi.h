#ifndef SPI_H
#define SPI_H

#include "avr.h"

void spi_init();

char spi_transmit_byte(char byte);

#endif // SPI_H