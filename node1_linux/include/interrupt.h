#ifndef INTERRUPT_H
#define INTERRUPT_H
#include "avr.h"
#include "avr/interrupt.h"

#include <stdio.h>

/**
 * @brief Run ONCE at start of main loop
 * 
 */
void configure_interrupts();

#endif // INTERRUPT_H