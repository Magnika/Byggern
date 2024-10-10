#ifndef SPI_H
#define SPI_H

#include "avr.h"
#include <string.h>

/**
 * @brief Initializes SPI as master
 * 
 */
void spi_init();

/**
 * @brief Transmits a set of bytes. Reads the response (MISO) from SPI data register.
 * num is number of bytes you want to send, ex: instruction, address, data => num=3
 * 
 * @param bytes 
 * @return char 
 */
char spi_transmit_byte(char* bytes, int length);

#endif // SPI_H