#ifndef SPI_H
#define SPI_H

#include "avr.h"

/**
 * @brief Initializes SPI as master
 * 
 */
void spi_init();

/**
 * @brief Transmits a single byte. Reads the response (MISO) from SPI data register.
 * 
 * @param byte 
 * @return char 
 */
char spi_transmit_byte(char byte);

#endif // SPI_H