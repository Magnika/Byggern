#include "include/spi.h"


void spi_init()
{
    /* Set MOSI and SCK output, all others input */
    DDRB = (1<<DDB5)|(1<<DDB7);
    /* Enable SPI, Master, set clock rate fck/16 */
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}


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
