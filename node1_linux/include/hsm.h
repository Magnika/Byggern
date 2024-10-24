#ifndef HSM_H
#define HSM_H

#include <stdint.h>
#include "oled.h"

typedef enum
{
    EVENT_ENTRY,
    EVENT_EXIT,
    EVENT_NAN,
    EVENT_JOYSTICK_UP,
    EVENT_JOYSTICK_DOWN,
    EVENT_JOYSTICK_PUSHED
} hsm_events_t;

typedef void (*state_function)(uint8_t event);

state_function state;

/**
 * @brief State function for menu in option 1
 * 
 * @param event 
 */
static void state_option_1(uint8_t event);

/**
 * @brief State function for menu in option 2
 * 
 * @param event 
 */
static void state_option_2(uint8_t event);

/**
 * @brief State function for menu in option 3
 * 
 * @param event 
 */
static void state_option_3(uint8_t event);


/**
 * @brief Start the HSM
 * 
 */
void hsm_run();

#endif // HSM_H