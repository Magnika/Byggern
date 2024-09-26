#include "joystick.h"

void joystick_read(struct JoystickVoltage* pJoystickVoltage)
{
    sram_write((int *) 0x1401, (uint8_t) 0b0);
    _delay_us(300);
    pJoystickVoltage->xValue = sram_read((int *) 0x1401);
    pJoystickVoltage->yValue = sram_read((int *) 0x1401);
}