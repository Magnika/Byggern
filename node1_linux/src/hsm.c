#include "hsm.h"

static void hsm_transition(state_function new_state)
{
    hsm_dispatch(EVENT_EXIT);
    state = new_state;
    hsm_dispatch(EVENT_ENTRY);
}

void hsm_dispatch(uint8_t event)
{
    state(event);
}

void hsm_run()
{
    state=&state_option_1;
    hsm_dispatch(EVENT_ENTRY);
}

static void state_option_1(uint8_t event)
{
    switch (event)
    {
    case EVENT_ENTRY:
        printf("Entering option 1\n\r");
        oled_clear_cursor();
        oled_print_cursor_at_option(1);
        break;
    case EVENT_JOYSTICK_UP:
        hsm_transition(state_option_3);
        break;
    case EVENT_JOYSTICK_DOWN:
        hsm_transition(state_option_2);
        break;
    case EVENT_JOYSTICK_PUSHED:
        // Transition to submenu or start playing
        break;
    case EVENT_EXIT:
        break;
    default:
        break;
    }
}

static void state_option_2(uint8_t event)
{
    switch (event)
    {
    case EVENT_ENTRY:
        printf("Entering option 2\n\r");
        oled_clear_cursor();
        oled_print_cursor_at_option(2);
        break;
    case EVENT_JOYSTICK_UP:
        hsm_transition(state_option_1);
        break;
    case EVENT_JOYSTICK_DOWN:
        hsm_transition(state_option_3);
        break;
    case EVENT_JOYSTICK_PUSHED:
        // Transition to submenu or start playing
        break;
    case EVENT_EXIT:
        break;
    default:
        break;
    }
}

static void state_option_3(uint8_t event)
{
    switch (event)
    {
    case EVENT_ENTRY:
        printf("Entering option 3\n\r");
        oled_clear_cursor();
        oled_print_cursor_at_option(3);
        break;
    case EVENT_JOYSTICK_UP:
        hsm_transition(state_option_2);
        break;
    case EVENT_JOYSTICK_DOWN:
        hsm_transition(state_option_1);
        break;
    case EVENT_JOYSTICK_PUSHED:
        // Transition to submenu or start playing
        break;
    case EVENT_EXIT:
        break;
    default:
        break;
    }
}