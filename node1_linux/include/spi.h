#ifndef SPI_H
#define SPI_H

#include "avr.h"
#include <string.h>
#include <stdio.h>
#include <util/delay.h> // Delay functions

/**
 * @brief Unset the Slave Select
 * 
 */
void unset_CS();

/**
 * @brief Set the Slave Select
 * 
 */
void set_CS();

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
void spi_transmit_bytes(char* bytes, int length, int lenghtReceive, char* response);

/**
 * @brief Transmit a single byte over SPI. Intended to be a simpler alternative to transmitting all the bytes.
 * 
 * \warning Does not set or unset slave select automatically.
 * 
 */
void spi_transmit_byte(char data);

/**
 * @brief Read a single byte. Sends a dummy byte the trigger a read.
 * 
 * @return char 
 */
char spi_read();

#endif // SPI_H