#include "include/pwm.h"

#define P_PWM 0.02         //Period of PWM signal [s]
#define DCL_PWM 0.0009     //Duty cycle of PWM signal [s]
#define chadAdress (*(Pwm*)0x40094200)
#define PWM_PERIOD (P_PWM * F_CPU/64.0)

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
    REG_PWM_CPRD1 = (int) (PWM_PERIOD);

    /* Set update mode 1*/
    REG_PWM_SCM |= PWM_SCM_UPDM_MODE1;


    /* Configure the duty cycle. Start at lowest valid duty cycle */
    REG_PWM_CDTY1 = (int) (PWM_PERIOD - PWM_MIN_DUTY_CYCLE_PERCENTAGE*PWM_PERIOD/100);

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

    /* Enble PWM on channel 1 */
    REG_PWM_ENA = PWM_ENA_CHID1;

    ////////////////////////////////////////////////////

    // Motor Setup
    // Give power to motor
    PMC->PMC_PCER0 |= (1 << ID_PIOB) | (1 << ID_PIOC);
    // Relinquish GPIO control of the PB12 pin.
    PIOB->PIO_ABSR |= PIO_ABSR_P12;
    PIOB->PIO_PDR |= PIO_PDR_P12;

    // Give GPIO control of PC23 pin
    PIOC->PIO_PER |= PIO_PER_P23;
    PIOC->PIO_OER |= PIO_OER_P23;

    // Configure motor channel for 1Mhz clock, 20kHz frequency
    PWM->PWM_CLK |= PWM_CLK_PREA(0) | PWM_CLK_DIVA(84);
    PWM->PWM_CH_NUM[0].PWM_CMR = PWM_CMR_CPRE_CLKA; // Use clock A for motor PWM
    PWM->PWM_CH_NUM[0].PWM_CPRD = 50; // 20Khz
    PWM->PWM_CH_NUM[0].PWM_CMR &= ~(1 << 8); // Set left aligned
    PWM->PWM_CH_NUM[0].PWM_CMR |= PWM_CMR_CPOL; // Set high polarity

    // Enable PWM motor channel
    PWM->PWM_ENA |= PWM_ENA_CHID0;
}

void pwm_set_duty_cycle(int percentage)
{
    float percentage_scaled = percentage*(PWM_MAX_DUTY_CYCLE_PERCENTAGE-PWM_MIN_DUTY_CYCLE_PERCENTAGE)/100.0 + PWM_MIN_DUTY_CYCLE_PERCENTAGE;
    
    if(percentage_scaled > PWM_MAX_DUTY_CYCLE_PERCENTAGE)
    {
        percentage_scaled = PWM_MAX_DUTY_CYCLE_PERCENTAGE;
    }
    if(percentage_scaled < PWM_MIN_DUTY_CYCLE_PERCENTAGE)
    {
        percentage_scaled = PWM_MIN_DUTY_CYCLE_PERCENTAGE;
    }

    float duty_cycle = percentage_scaled*PWM_PERIOD/100.0;

    REG_PWM_CDTYUPD1 = (uint32_t) (PWM_PERIOD - duty_cycle);
}

void pwm_motor_set_duty_cycle(int percentage)
{
    PWM->PWM_CH_NUM[0].PWM_CDTY = (uint32_t) PWM->PWM_CH_NUM[0].PWM_CPRD*percentage/100;
}

void pwm_set_motor_direction(int direction)
{
    if(direction)
    {
        PIOC->PIO_SODR = PIO_SODR_P23;
    }
    else
    {
        PIOC->PIO_CODR = PIO_CODR_P23;
    }
}