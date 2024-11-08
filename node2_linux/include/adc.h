#include "sam.h"

#define THRESHOLD_VOLTAGE 2 //Volt


void adc_init();

void ADC_Handler(void);

void print_adc_value(void);

uint16_t adc_read_channel_0(void);