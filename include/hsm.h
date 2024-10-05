#ifndef HSM_H
#define HSM_H

#include <stdint.h>
#include "oled.h"

typedef enum
{
    EVENT_ENTRY,
    EVENT_EXIT,
    EVENT_JOYSTICK_UP,
    EVENT_JOYSTICK_DOWN,
    EVENT_JOYSTICK_PUSHED
} hsm_events_t;

typedef void (*state_function)(uint8_t event);

state_function state;

void hsm_run();

#endif // HSM_H