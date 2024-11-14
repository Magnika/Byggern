#include "include/game.h"

joystickPosition_t joystick_pos;

void update_joystick_pos(int x, int y, int isNotPushed)
{
    joystick_pos.x = x;
    joystick_pos.y = y;

    if(!isNotPushed)
    {
        joystick_pos.isbuttonPushed = 1;
    }
    else{
        joystick_pos.isbuttonPushed = 0;
    }
    
}