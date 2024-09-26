#include "joystick.h"

void joystick_read(struct JoystickVoltage* pJoystickVoltage, struct SliderVoltage* pSliderVoltage)
{
    sram_write((int *) 0x1401, (uint8_t) 0b0);
    _delay_us(300);
    pJoystickVoltage->xValue = sram_read((int *) 0x1401);
    pJoystickVoltage->yValue = sram_read((int *) 0x1401);
    pSliderVoltage->sliderA = sram_read((int *) 0x1401);
    pSliderVoltage->sliderB = sram_read((int *) 0x1401);
}

float joystick_voltage_to_angle_x(uint8_t voltage)
{
    float xPos = 0;

    return xPos;
}

float joystick_voltage_to_angle_y(uint8_t voltage)
{
    float yPos = 0;

    return yPos;
}

float joystick_voltage_to_slider(uint8_t voltage)
{
    float sliderPos = 0;
    // TODO: Convert voltage to position

    return sliderPos;
}