#ifndef USART_H
#define USART_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "avr.h"

void USART_Init( unsigned int ubrr );

void USART_Transmit( unsigned char data );

void USART_print_string(const char* string);

unsigned char USART_Receive( void );

void testUSART_Receive();

#endif // USART_H

