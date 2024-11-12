#include "sam.h"
#include "include/uart.h"
#include "component/component_adc.h"
#include "include/adc.h"

void adc_init() {
    // Enable clock for ADC  
    PMC->PMC_PCER1 |= PMC_PCER1_PID37;

    // Free Run Mode: Never wait for any trigger
    ADC->ADC_MR = ADC_MR_FREERUN;

    // Enable channel 0
    ADC->ADC_CHER = ADC_CHER_CH0;

    // Start analog-to-digital conversion
    ADC->ADC_CR = ADC_CR_START;
}


uint16_t adc_read() {
    /*The analog-to-digital conversion data is placed into this register at the end of a conversion and remains until a new conver-
    sion is completed. The Convert Data Register (CDR) is only loaded if the corresponding analog channel is enabled*/

    return ADC->ADC_CDR[0];
}