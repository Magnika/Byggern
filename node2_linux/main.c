#include <stdio.h>
#include <stdarg.h>
#include "sam.h"
#include "include/uart.h"
#include "include/time.h"

#define CPU_FREQ 84000000
#define UART_BAUD 9600

int main()
{
    SystemInit();
    WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer

    uart_init(CPU_FREQ, UART_BAUD);
    printf("Hello World\n\r");

    while (1)
    {
        time_spinFor(msecs(1000));
        printf("Loop iteration\n\r");
    }
    
}