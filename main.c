//#define F_CPU 4915200// Clock Speed
#define F_CPU 8e6// Clock Speed
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

#include "include/usart.h" // USART support
#include "include/avr.h"
#include "include/sram_test.h"
#include "include/decoder_test.h"
#include "include/sram.h"
#include "include/joystick.h"
#include "include/oled.h"

#include <util/delay.h> // Delay functions
#include <stdio.h>

static void avr_pwm_configure()
{
    TCCR1A = (1 << WGM10) | (1 << WGM11) | (1 << COM1A0) | (0 << COM1A1);
    OCR1A = 0x0000;
    //Side 132 i datablad. Still in PWM frekvens clk/256
    TCCR1B = (1 << WGM12) | (1 << WGM13) | (0 << CS12) | (1 << CS11) | (0 << CS10); 
    DDRD |= (1 << DD5);
}

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
    avr_pwm_configure();
    
    _delay_us(1000);
    oled_init();
    _delay_us(1000);  
    oled_write_c(0xa4);

    while (1)
    {
        
        
        _delay_us(50);        
    }
    
}
