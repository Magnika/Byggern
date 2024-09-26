#include "adc.h"

void setHardWired()
{
    TCCR1A = (1 << WGM10) | (1 << WGM11) | (1 << COM1A0) | (1 << COM1A1);
    OCR1A = 0x0000;

    TCCR1B = (1 << WGM12) | (1 << WGM13);

    DDRD |= (1 << DD5);
}