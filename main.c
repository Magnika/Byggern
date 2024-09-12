//#define F_CPU 4915200// Clock Speed
#define F_CPU 8e6// Clock Speed
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

#include "usart.h" // USART support

#include <util/delay.h> // Delay functions

void main( void )
{
    USART_Init ( MYUBRR );
    while (1)
    {
        ymsePrint("Hello");
        _delay_ms(2000);
    }
}
