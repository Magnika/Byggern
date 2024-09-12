#ifndef USART_H
#define USART_H

#define __AVR_ATmega162__ // Get port definitions for ATMega162

#include <stdint.h>
#include <avr/io.h>
#include <string.h>

void USART_Init( unsigned int ubrr );

void USART_Transmit( unsigned char data );

void USART_print_string(const char* string);

#endif // USART_H

