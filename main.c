//#define F_CPU 4915200// Clock Speed
#define F_CPU 8e6// Clock Speed
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

#include "include/usart.h" // USART support

#include <util/delay.h> // Delay functions

/**
 * @brief Set the SRE bit in the MCUCR register. This enables the use of external SRAM.'
 * @details Writing SRE to one enables the External Memory Interface.The pin functions AD7:0, A15:8,
    ALE, WR, and RD are activated as the alternate pin functions. The SRE bit overrides any pin
    direction settings in the respective Data Direction Registers. Writing SRE to zero, disables the
    External Memory Interface and the normal pin and data direction settings are used.
 * 
 */
void SRE_bit_enable()
{
    MCUCR |= 0b10000000;
}

void main( void )
{
    USART_Init ( MYUBRR );
    SRE_bit_enable();
    while (1)
    {
        //USART_print_string("Hello");
        testUSART_Receive();
        _delay_ms(200);
    }
}
