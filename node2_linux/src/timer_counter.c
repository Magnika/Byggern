#include "include/timer_counter.h"
#include "include/time.h"
#include "include/game.h"


void timer_counter_init()
{
    /* Clear the write protection bit */
    TC0->TC_WPMR |= (0x54494D << SMC_WPCR_WP_KEY_Pos);
    TC0->TC_WPMR &= 0xFFFFFFFF & ~(TC_WPMR_WPEN);

    // Enable peripheral clock
    REG_PMC_PCER0 |= (1 << ID_TC0);

    /* Set the TC Channel 0 Mode Register */
    // Clock select MCK/128
    // Waveform mode enable
    // RC Compare Resets the counter
    TC0->TC_CHANNEL[0].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK4 | TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC;

    // Set RC register for 20ms interval
    TC0->TC_CHANNEL[0].TC_RC = F_CPU/128/TIMER_INTERRUPT_FREQUENCY_HZ;

    /* Enable RC compare interrupt on Register C */
    TC0->TC_CHANNEL[0].TC_IER = TC_IER_CPCS;

    /* Enable the TC0 interrupt in NVIC */
    NVIC_EnableIRQ(TC0_IRQn);

    /* Start the Timer */
    TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
}

CanMsg msg;

void TC0_Handler(void)
{
    if(TC0->TC_CHANNEL[0].TC_SR & TC_SR_CPCS)
    {  
        int joystick_angle_x = (int) joystick_pos.x;

        //Since DT is set by percentage and voltage ranges from 0 to 200, devide by two
        pwm_set_duty_cycle((int)(joystick_angle_x / 2));
    }
}