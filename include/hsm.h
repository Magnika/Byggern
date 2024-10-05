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

static void state_option_1(uint8_t event);
static void state_option_2(uint8_t event);
static void state_option_3(uint8_t event);

void hsm_run();

#endif // HSM_H