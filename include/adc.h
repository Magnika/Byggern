#ifndef ADC_H
#define ADC_H

#include "avr.h";

#define PWM_FREQ 10000 // 10kHz
#define ADC_MEM_ADDR 0x1500 // Address inside ADC address space. Any between 0x1400-0x1800 will do.

void adc_setHardWired();
void adc_setChipSelect();
void adc_unsetChipSelect();
void adc_setRead();
void adc_setWrite();

unsigned char adc_read();


#endif // ADC_H