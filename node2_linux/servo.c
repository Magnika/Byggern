#include "servo.h"

#define P_PWM 0.02         //Period of PWM signal [s]
#define DCL_PWM 0.0009     //Duty cycle of PWM signal [s]
#define chadAdress (*(Pwm*)0x40094200)

void servo_test()
{
    //Deaktiverer protection mot å skriving til PIOB
    PIOB->PIO_WPMR = 0x50494F00;
    //Setter PIOB13 til å være en output
    PIOB->PIO_PER = PIO_PB13;

    //Allow writing to PWM registers
    PWM->PWM_WPCR = 0x50574D << 8;

    //Deactivating write protect on all PWM registers
    PWM->PWM_WPCR = 0b111111 << 2;
    PWM->PWM_WPCR = 0b00;

    PWM->PWM_CMP
    

    //Config of the clk generator = F_CPU/(64)
    PWM->PWM_CLK = PWM_CLK_PREB(0) | PWM_CLK_DIVB(64);

    //Config of the period
    REG_PWM_CPRD1 = P_PWM * F_CPU/64;

    //Config of the duty cycle
    REG_PWM_CDTY1 = (int)(1/DCL_PWM);

    //Enabler PWM på kanal 1
    PWM->PWM_ENA = PWM_ENA_CHID1;


}