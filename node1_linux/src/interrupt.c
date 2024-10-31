#include <avr/interrupt.h>

void configure_interrupts()
{
    // Set INT1 to trigger on rising edge
    MCUCR |= (1 << ISC11) | (1 << ISC10);

    // Set INT0 to trigger on rising edge
    MCUCR |= (1 << ISC01) | (1 << ISC00);

    // Clear INT2 in GICR register
    GICR = (0 << INT2);

    // Set INT2 to trigger on falling edge
    EMCUCR = (0 << ISC2);

    // Clear INT2 interrupt flag
    GIFR |= (1 << INTF2);

    // Set INT1 and INT0 to enable external interrupt
    GICR |= (1 << INT2) | (1 << INT1) | (1 << INT0);

    // Global interrupt enable
    SREG |= (1 << SREG_I);
}

