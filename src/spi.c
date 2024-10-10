#include "spi.h"


void spi_init()
{
    /* Set MOSI and SCK output, all others input */
    DDRB = (1<<DDB5)|(1<<DDB7)|(1<<DDB4);
    /* Enable SPI, Master, set clock rate fck/16 */
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
    /*Set Chip select high*/
    PORTB = (1<<PB4);
}


char spi_transmit_byte(char* bytes, int length)
{
    /* Set SS' low */
    PORTB = (0<<PB4);

    for(int i=0;i<length; i++)
    {
        /* Send byte transmission */
        SPDR = bytes[i];
        /* Wait for transmission complete */
        while(!(SPSR & (1<<SPIF)));
    }

    /* Read response in SPDR */
    char response = SPDR;
    
    /* Set SS' high */
    PORTB = (1<<PB4);

    return response;
}
