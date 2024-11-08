#include <stdio.h>
#include <stdarg.h>
#include "sam.h"
#include "include/uart.h"
#include "include/time.h"
#include "include/can.h"
#include "include/pwm.h"
#include "include/timer_counter.h"
#include "include/adc.h"

#define CPU_FREQ 84000000
#define UART_BAUD 9600

int main()
{
    SystemInit();
    WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer

    uart_init(CPU_FREQ, UART_BAUD);
    printf("Hello World\n\r");

    pwm_init();
    timer_counter_init();
    
    CanInit can_settings;
    can_settings.reg = CAN_BR_SETTINGS;
    can_init(can_settings, 1);

    adc_init();

    
    while (1)
    {   
        print_adc_value();
        time_spinFor(msecs(2000));
    }
    
}