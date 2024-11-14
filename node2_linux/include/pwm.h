#ifndef PWM_H
#define PWM_H

#include "sam.h"
#include "uart.h"
#include "component/component_pwm.h"


#define F_CPU 84e6
#define PWM_MAX_DUTY_CYCLE_PERCENTAGE 10.0
#define PWM_MIN_DUTY_CYCLE_PERCENTAGE 5.0

/**
 * @brief Set the duty cycle of the PWM output
 * 
 */
void pwm_set_duty_cycle(int percentage);

/**
 * @brief Initialize the PWM module
 * 
 */
void pwm_init();

void pwm_motor_set_duty_cycle(int duty_cycle_percent);

void pwm_set_motor_direction(int direction);

void solenoid_init();

void solenoid_punch();

void solenoid_retract();

#endif // PWM_H