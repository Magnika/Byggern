#ifndef TIMER_COUNTER_H
#define TIMER_COUNTER_H

#include "sam.h"
#include "uart.h"
#include "component/component_tc.h"
#include "component/component_pmc.h"
#include "can.h"
#include "pwm.h"
#include "include/time.h"

#define F_CPU (84e6)
#define TIMER_INTERRUPT_FREQUENCY_HZ 50

/**
 * @brief Init all timer counter functionality
 * 
 * \details Each channel has three external clock inputs, five internal clock inputs and two multi-purpose input/output signals
            which can be configured by the user. Each channel drives an internal interrupt signal which can be programmed to
            generate processor interrupts.
 * 
 */
void timer_counter_init();



#endif // TIMER_COUNTER_H