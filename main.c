//#define F_CPU 4915200// Clock Speed
#define F_CPU 8e6// Clock Speed
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

#include "include/usart.h" // USART support
#include "include/sram_test.h"

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
    //MCUCR |= 0b10000000;
    MCUCR = (1<<SRE);
}

/**
* @brief Activtes pull up  resistors on AD7:0 ports.
* @details The pull-up resistors on the AD7:0 ports may be activated if the corresponding Port register is
    written to one. To reduce power consumption in sleep mode, it is recommended to disable the
    p   ull-ups by writing the Port register to zero before entering sleep.

**/
void AD70_pullup_activate()
{
    PORTA = (1<<PA0) | (1<<PA1) | (1<<PA2) | (1<<PA3) | (1<<PA4) | (1<<PA5) | (1<<PA6) | (1<<PA7);
}

void test_EXT_MEM()
{
    SRAM_init();

    SRAM_test();
}

void SRAM_init()
{
    SRE_bit_enable();
    AD70_pullup_activate();
    SFIOR = (0<<XMM1) | (0<<XMM0) | (1<<XMM2);
}

void custom_test_SRAM()
{
    SRAM_init();
    volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
    uint16_t ext_ram_size = 0x800;

    ext_ram[1] = (uint8_t) 69;
    printf("Just wrote nice number");
    uint8_t received = ext_ram[1];
    printf("Just received %d", received);
}


void main( void )
{
    USART_Init ( MYUBRR );
    stdout = &usart_std_out;

    test_EXT_MEM();
    /*
    while (1)
    {
        //USART_print_string("Hello");
        testUSART_Receive();
        _delay_ms(200);
    }
    */
}
