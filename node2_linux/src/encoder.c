#include "include/encoder.h"
#include "uart.h"
#include "component/component_tc.h"
#include "component/component_pmc.h"

void encoder_init()
{
    // Enable the peripheral clock
    PMC->PMC_PCER0 |= (1 << ID_TC2);

    TC2->TC_BMR = TC_BMR_QDEN | TC_BMR_POSEN | TC_BMR_EDGPHA | TC_BMR_FILTER;

    //TC2->TC_CHANNEL
    


}

uint16_t encoder_sample()
{
    return 0;
}