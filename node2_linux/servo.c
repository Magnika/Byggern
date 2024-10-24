#include "servo.h"

#define P_PWM 0.02         //Period of PWM signal [s]
#define DCL_PWM 0.0009     //Duty cycle of PWM signal [s]
#define chadAdress (*(Pwm*)0x40094200)

void pwm_init()
{
    //Give power to PWM
    REG_PMC_PCER1 |= (1 << 4);

    /* Unlock user interface by writing the WPCMD field in PWM_WPCR Register */
    // Set write protect key
    PWM->PWM_WPCR = 0x50574D << 8;
    // Mark all register groups as modifieable
    PWM->PWM_WPCR = 0b111111 << 2;
    // Unlock user interface
    PWM->PWM_WPCR = 0b00;

    /* Disable the channel before configuring, this is a requirement to change duty cycle and period */
    REG_PWM_DIS = PWM_DIS_CHID1;

    /* Configure the clock generator */
    // Choose master clock, and divide by 64 (arbitrary number)
    REG_PWM_CLK = PWM_CLK_PREB(0) | PWM_CLK_DIVB(64);

    /* Select the clock for each channel */
    // Select clock B for channel 1
    REG_PWM_CMR1 |= 0b1100;

    /* Configure the period for each channel */
    REG_PWM_CPRD1 = (int) (P_PWM * F_CPU/64);


    /* Configure the duty cycle */
    REG_PWM_CDTY1 = (int) (P_PWM * F_CPU/64)/4;

    ////////////////////////////////////////////////////
    /////// Set the pin to be controlled by the PWM
    ////////////////////////////////////////////////////
    //Give power to PIO
    REG_PMC_PCER0 |= (1 << 12);

    //Remove write protection
    PIOB->PIO_WPMR = 0x50494F00;

    //Setter PIOB13 til å være peripheral B
    PIOB->PIO_ABSR = PIO_PB13;

    //Write enable PIO
    REG_PIOB_OWER |= (1 << 13);

    //Setter PIOB13 til å være en output
    PIOB->PIO_PER = PIO_PB13;

    //Remove PIO control of the pin
    REG_PIOB_PDR |= (1 << 13);
    
    ////////////////////////////////////////////////////

    /* Enble PWM on channel 1 */
    REG_PWM_ENA = PWM_ENA_CHID1;

}