#include "usart.h"

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

void USART_print_string(const char* string)
{
    for(int c=0; c<strlen(string); c++)
    {
        USART_Transmit(string[c]);
    }
}

unsigned char USART_Receive( void )
{
    /* Wait for data to be received */
    while ( !(UCSR1A & (1<<RXC1)) );
    
    /* Get and return received data from buffer */
    return UDR;
}

void testUSART_Receive()
{
    char message = USART_Receive();
    USART_print_string(message);
}