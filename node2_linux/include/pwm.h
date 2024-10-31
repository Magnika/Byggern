#ifndef PWM_H
#define PWM_H

#include "sam.h"
#include "uart.h"
#include "component/component_pwm.h"

#define F_CPU 84e6
#define PWM_MAX_DUTY_CYCLE 0.105
#define PWM_MIN_DUTY_CYCLE 0.045

/**
 * @brief Set the duty cycle of the PWM output
 * 
 */
void pwm_set_duty_cycle();

/**
 * @brief Initialize the PWM module
 * 
 */
void pwm_init();

#endif // PWM_H