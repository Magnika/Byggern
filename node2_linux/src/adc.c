#include "include/adc.h"


void adc_init()
{

    REG_ADC_WPMR = ADC_WPMR_WPKEY(0x414443) | //Write protection key
                    (0 << 0); //Disable write protect

    //Enable peripheral clock PID37
    REG_PMC_PCER1 |= (1 << (ID_ADC-32));

    PIOA->PIO_PDR = PIO_PA16;     // Disable GPIO control for PA16 (AD0)
    PIOA->PIO_ABSR &= ~PIO_PA16;  // Connect PA16 to Peripheral A (ADC)




    REG_ADC_MR = ADC_MR_TRGEN_DIS | //Disable hardware trigger
                ADC_MR_PRESCAL(8) | // ADC clock = MCK / (2 * (PRESCAL + 1)) = 84 MHz / 18 = ~4.67 MHz
                ADC_MR_STARTUP_SUT64 | //Start up time
                ADC_MR_TRACKTIM(15); //Tracking time =  (TRACKTIM + 1) * ADCClock periods

    //Enable ADC Channel 0
    REG_ADC_CHER |= ADC_CHER_CH0;

    //Configure comparison mode
    REG_ADC_EMR = ADC_EMR_CMPSEL(0) | //Compare channel 0
                    ADC_EMR_CMPMODE_LOW; //Set event when voltage goes below threashold

    //Set threshold
    uint16_t threshold = (THRESHOLD_VOLTAGE / 3.3) * 4095;
    REG_ADC_CWR = ADC_CWR_LOWTHRES(threshold) | //Sets lower threshold to 2V
                    ADC_CWR_HIGHTHRES(0xFFF); //Sets high threshold to max (Not in use)


    //Enable compare interupt
    REG_ADC_IER = ADC_IER_COMPE;

    //Enable ADC interupt in NVIC
    NVIC_EnableIRQ(ADC_IRQn);
}

void ADC_Handler(void)
{
    if (ADC->ADC_ISR & ADC_ISR_COMPE) {
        printf("ADC Interupt enabled\n\r");
    }

}


uint16_t adc_read_channel_0(void) {
    // Start the conversion
    ADC->ADC_CR = ADC_CR_START;

    // Wait for the conversion to complete
    while (!(ADC->ADC_ISR & ADC_ISR_EOC0));  // Wait for EOC (End of Conversion) for Channel 0

    // Read and return the conversion result from Channel Data Register 0
    return (uint16_t)(ADC->ADC_CDR[0]);
}

void print_adc_value(void) {
    // Read ADC value from Channel 0
    uint16_t adc_value = adc_read_channel_0();

    // Convert ADC value to voltage (for 3.3V reference)
    float voltage = (adc_value * 3.3) / 4095.0;

    // Print the raw ADC value and corresponding voltage (Replace this with your debug method)
    // Example: UART or LED indication
    printf("ADC Value: %u, Voltage: %.2f V\n\r", adc_value, voltage);
}