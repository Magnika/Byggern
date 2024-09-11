//#define F_CPU 4915200// Clock Speed
#define F_CPU 8e6// Clock Speed
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h> // Delay functions

#include <string.h>

void USART_Init( unsigned int ubrr )
{
    /* Set baud rate */
    UBRR1H = (unsigned char)(ubrr>>8);
    UBRR1L = (unsigned char)ubrr;
    
    /* Enable receiver and transmitter */
    UCSR1B = (1<<RXEN1)|(1<<TXEN1);
    
    /* Set frame format: 8data, 2stop bit */
    UCSR1C = (1<<URSEL1)|(1<<USBS1)|(3<<UCSZ01);
}

void USART_Transmit( unsigned char data )
{
    /* Wait for empty transmit buffer */
    while ( !( UCSR1A & (1<<UDRE1)));
    /* Put data into buffer, sends the data */
    UDR1 = data;
}

void ymsePrint(const char* string)
{
    for(int c=0; c<strlen(string); c++)
    {
        USART_Transmit(string[c]);
    }
}



void main( void )
{

    USART_Init ( MYUBRR );
    while (1)
    {
        ymsePrint("Hello");
        _delay_ms(2000);
    }
    

}


    