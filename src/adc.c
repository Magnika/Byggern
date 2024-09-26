#include "adc.h"

void setHardWired()
{
    TCCR1A = (1 << WGM10) | (1 << WGM11) | (1 << COM1A0) | (0 << COM1A1);
    OCR1A = 0x0000;
    //Side 132 i datablad. Still in PWM frekvens clk/256
    TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS12) | (0 << CS11) | (0 << CS10);

    DDRD |= (1 << DD5);
}