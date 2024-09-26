#ifndef ADC_H
#define ADC_H

#include "avr.h";

#define PWM_FREQ 10000 // 10kHz

void setHardWired();

/**
 * @brief Read data from the ADC data pins
 * 
 */
void readData()
{
    // Set CS low
    // Set RD low
    // Read D0-D7
}

#endif // ADC_H