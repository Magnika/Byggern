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

int get_joystick_angle_x()
{
    uint8_t voltage = joystickVoltage.xValue;
    float angle_f = ((float) voltage - (255.0f/2))/128.0f;
    int angle = (int) (angle_f * 100);

    return angle;
}

int get_joystick_angle_y()
{
    uint8_t voltage = joystickVoltage.yValue;
    float angle_f = ((float) voltage - (255.0f/2))/128.0f;
    int angle = (int) (angle_f * 100);

    return angle;
}

int get_slider_pos(uint8_t voltage)
{
    float angle_f = ((float) voltage)/255.0f;
    int pos = (int) (angle_f * 100);

    return pos;
}