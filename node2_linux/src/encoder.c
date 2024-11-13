#include "include/encoder.h"
#include "include/uart.h"
#include "component/component_tc.h"
#include "component/component_pmc.h"

void encoder_init()
{
    /*
        PC25 and PC26 are used by channel 0 of TC2 when in QDEC mode.
        QDEC mode requires setting the block mode register, which will change the operating mode of the entire TC2 instance.
        You must also select XC0 as the selected clock for channel 0.
    */
    PIOC->PIO_PDR |= PIO_PC25 | PIO_PC26;  // Disable the PIO controller to use peripheral function
    PIOC->PIO_ABSR |= (PIO_ABSR_P25 | PIO_ABSR_P26);  // Set pins to peripheral B mode

    // Enable the peripheral clock
    PMC->PMC_PCER1 |= (1 << 1);

    // QD mode, position read
    TC2->TC_BMR = TC_BMR_QDEN | TC_BMR_POSEN | TC_BMR_EDGPHA;

    // Set XC0 as clock
    // Set wave to 0 on channel 0 and 1
    /* ‘Rising edge’ must be selected as the External Trigger Edge (TC_CMR.ETRGEDG = 0x01) and ‘TIOA’ must be selected as the External Trigger
        (TC_CMR.ABETRG = 0x1).*/
    TC2->TC_CHANNEL[0].TC_CMR = (TC_CMR_TCCLKS_XC0 |        // Set XC0 as the clock source
                                TC_CMR_ETRGEDG_RISING |     // External trigger on rising edge
                                TC_CMR_ABETRG &             // External trigger source from TIOA
                                (~(1 << 15)));              // Disable WAVE

    TC2->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
}

uint32_t encoder_sample()
{
    /* 
    In parallel, the number of edges are accumulated on timer/counter channel 0 and can be read on the TC_CV0 register.
    Therefore, the accurate position can be read on both TC_CV registers and concatenated to form a 32-bit word.
    The timer/counter channel 0 is cleared for each increment of IDX count value.
    TC_QISR is direction status (0 or 1).

    */
   uint32_t measurement = TC2->TC_CHANNEL[0].TC_CV;
   uint32_t direction = TC2->TC_QISR;
   printf("In encoder.c: measurement=%d\n\r", measurement);

   return measurement;
}