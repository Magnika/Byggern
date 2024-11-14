#include <stdio.h>
#include <stdarg.h>
#include "sam.h"
#include "include/uart.h"
#include "include/time.h"
#include "include/can.h"
#include "include/pwm.h"
#include "include/timer_counter.h"
#include "include/adc.h"
#include "include/encoder.h"
#include "include/game.h"

#define CPU_FREQ 84000000
#define UART_BAUD 9600

int update_and_return_score()
{
    static int score = 0;
    static ir_threshold = 4000;

    if(adc_read() < ir_threshold)
    {
        score++;
    }

    return score;
}

int main()
{
    SystemInit();
    WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer

    uart_init(CPU_FREQ, UART_BAUD);
    printf("Hello World\n\r");

    pwm_init();
    timer_counter_init();
    adc_init();
    encoder_init();
    solenoid_init();

    
    CanInit can_settings;
    can_settings.reg = CAN_BR_SETTINGS;
    can_init(can_settings, 1);

    
    while (1)
    {
        //uint32_t pos_meas = encoder_sample();
        //printf("Encoder measurement=%f\n\r", 100*pos_meas/ENCODER_RANGE);
        //pwm_motor_set_duty_cycle(30);
        //printf("Loop iteration\n\r");

        // PIOC->PIO_SODR |= PIO_SODR_P24;
        // //Possible delay necessary here
        // time_spinFor(msecs(10));
        // PIOC->PIO_CODR |= PIO_CODR_P24;
        // time_spinFor(msecs(10));




    }
    
}