#include "include/game.h"

joystickPosition_t joystick_pos;

void update_joystick_pos(int x, int y, int isButtonPushed)
{
    joystick_pos.x = x;
    joystick_pos.y = y;
    joystick_pos.isbuttonPushed = isButtonPushed;
}