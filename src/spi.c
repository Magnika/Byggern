#include "include/spi.h"

/**
 * @brief Initializes SPI as master
 * 
 */
void spi_init()
{
/* Set MOSI and SCK output, all others input */
DDRB = (1<<DDB5)|(1<<DDB7);
/* Enable SPI, Master, set clock rate fck/16 */
SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

/**
 * @brief Transmits a single byte. Reads the response (MISO) from SPI data register.
 * 
 * @param byte 
 * @return char 
 */
char spi_transmit_byte(char byte)
{
/* Start transmission */
SPDR = byte;
/* Wait for transmission complete */
while(!(SPSR & (1<<SPIF)));

/* Read response in SPDR */
char response = SPDR;
return response;
}
