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
#include "include/hsm.h"
#include "include/spi.h"
#include "include/mcp2515.h"
#include "include/can_node1.h"

#include "include/interrupt.h"

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
    joystick_init();
    configure_interrupts();

    spi_init();
    can_init();
    
    oled_init();
    oled_print_menu();
    hsm_run();

    uint8_t event;
    while (1)
    {
        joystick_update(&joystickVoltage, &sliderVoltage, &joystickState);
        if(joystickState.isJoystickActuatedYRisingEdge==1)
        {
            event = EVENT_JOYSTICK_UP;
        }
        else if(joystickState.isJoystickActuatedYRisingEdge==-1)
        {
            event = EVENT_JOYSTICK_DOWN;
        }
        
        else if(joystickState.isButtonPressedRisingEdge)
        {
            event = EVENT_JOYSTICK_PUSHED;
        }

        else
        {
            event = EVENT_NAN;
        }
        hsm_dispatch(event);
        
        char string[8] = "Hallaien";
        can_frame_t test_frame;
        test_frame.id = 128;
        test_frame.data_length = 8;
        
        for(uint8_t i=0; i<8; i++)
        {
            test_frame.data[i]=string[i];
        }

        can_transmit(&test_frame);
        _delay_ms(10);
        
    }
    
}

// CONFIGURE INTERRUPST IN MAIN, DOES NOT WORK IN C OR HEADER FOR SOME REASON
ISR(INT0_vect)
{
    // TODO: Implement
    printf("ISR0 executed\n\r");
}

ISR(INT1_vect)
{
    // TODO: Implement
    printf("ISR1 executed\n\r");
}

ISR(INT2_vect)
{
    // CAN CONTROLLER
    // Find out which CAN interrupt triggered by reading CANINTF
    can_frame_t msg;
    can_read(&msg);
    printf("Received %d bytes from ID %d\n\r", msg.data_length, msg.id);

    mcp2515_bit_modify(CANINTF_ADDR, 0b00000001, 0b0); // Unset the interrupt flag at the can controller. This must be done manually or the intf is always raised.
}
