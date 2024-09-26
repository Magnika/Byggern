//#define F_CPU 4915200// Clock Speed
#define F_CPU 8e6// Clock Speed
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

#include "include/usart.h" // USART support
#include "include/avr.h"
#include "include/sram_test.h"
#include "include/decoder_test.h"
#include "include/sram.h"
#include "include/adc.h"

#include <util/delay.h> // Delay functions
#include <stdio.h>

static int USART_put_char(char c, FILE *stream)
{
    while ( !( UCSR1A & (1<<UDRE1)));
    UDR1 = c;
    
    return 0;
}

static int USART_get_char(FILE *stream)
{
    /* Wait for data to be received */
    while ( !(UCSR1A & (1<<RXC1)) );
    
    /* Get and return received data from buffer */
    return UDR1;
}

static FILE usart_std_out = FDEV_SETUP_STREAM(USART_put_char, USART_get_char, _FDEV_SETUP_RW);

void main( void )
{
    USART_Init ( MYUBRR );
    stdout = &usart_std_out;

    SRAM_init();

    adc_setHardWired();
    //test_decoder();

    while (1)
    {
        //USART_print_string("Hello");
        //test_decoder();
        _delay_ms(10);
        //SRAM_test();
    }
    
}
