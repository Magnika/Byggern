#include <stdio.h>
#include <stdarg.h>
#include "sam.h"
#include "include/uart.h"
#include "include/time.h"
#include "include/can.h"
#include "include/pwm.h"
#include "include/timer_counter.h"

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

    CanMsg msg;
    while (1)
    {
        pwm_set_duty_cycle(100);
        time_spinFor(msecs(2000));
        pwm_set_duty_cycle(0);
        time_spinFor(msecs(2000));
        pwm_set_duty_cycle(30);
        time_spinFor(msecs(2000));
        printf("Loop iteration\n\r");
    }
    
}