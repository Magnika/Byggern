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


void spi_transmit_bytes(char* bytes, int length, int lenghtReceive, char* response)
{
    /* Set SS' low */
    unset_CS();

    for(int i=0;i<length; i++)
    {
        /* Send byte transmission */
        SPDR = bytes[i];
        /* Wait for transmission complete */
        while(!(SPSR & (1<<SPIF)));
    }

    for (int i=0; i<lenghtReceive; i++)
    {
        SPDR = 0xFF;
        while(!(SPSR & (1<<SPIF)));
        response[i] = SPDR;
    }
    /* Set SS' high */
    set_CS();

    _delay_us(50); // Delay is needed to correctly save response, don't know why.
}

void spi_transmit_byte(char data)
{
    SPDR = data;

    while(!(SPSR & (1<<SPIF)));
}

void set_CS()
{
    PORTB |= (1<<PB4);
}

void unset_CS()
{
    PORTB &= ~(1<<PB4);
}

char spi_read()
{
    // Trigger a receive
    spi_transmit_byte(0);
    return SPDR;
}
