#ifndef GAME_H
#define GAME_H

#include <stdint.h>

typedef struct JoystickPosition
{
    uint8_t x;
    uint8_t y;
    uint8_t isbuttonPushed;
} joystickPosition_t;

extern joystickPosition_t joystick_pos;

void update_joystick_pos(int x, int y, int isButtonPushed);

#endif // GAME_H