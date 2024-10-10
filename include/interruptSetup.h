#ifndef INTERRUPTSETUP_H
#define INTERRUPTSETUP_H
#include "avr.h"
#include "avr/interrupt.h"

/**
 * @brief Run ONCE at start of main loop
 * 
 */
void configure_interrupts()
{
    // Set INT1 to trigger on rising edge
    MCUCR |= (1 << ISC11) | (1 << ISC10);

    // Set INT0 to trigger on rising edge
    MCUCR |= (1 << ISC01) | (1 << ISC00);

    // Set INT2 to trigger on rising edge
    EMCUCR |= (1 << ISC2);

    // Set INT1 and INT0 to enable external interrupt
    GICR |= (1 << INT2) | (1 << INT1) | (1 << INT0);

    // Global interrupt enable
    SREG |= (1 << SREG_I);
}

ISR(INT0_vect)
{
    // TODO: Implement
}

ISR(INT1_vect)
{
    // TODO: Implement
}

ISR(INT2_vect)
{
    // CAN CONTROLLER
    // Find out which CAN interrupt triggered by reading CANINTF
}

#endif // INTERRUPTSETUP_H