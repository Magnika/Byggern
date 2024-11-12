#ifndef ADC_H
#define ADC_H

/**
 * @brief Initialise the ADC
 * 
 */
void adc_init();

/**
 * @brief Read the ADC
 * 
 * @return uint16_t 
 */
uint16_t adc_read();

#endif // ADC_H