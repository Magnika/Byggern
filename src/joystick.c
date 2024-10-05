#include "joystick.h"

void joystick_update(struct JoystickVoltage* pJoystickVoltage, struct SliderVoltage* pSliderVoltage, struct JoystickState* pJoystickState)
{
    sram_write((int *) 0x1401, (uint8_t) 0b0);
    _delay_us(300);
    pJoystickVoltage->xValue = sram_read((int *) 0x1401);
    pJoystickVoltage->yValue = sram_read((int *) 0x1401);
    pSliderVoltage->sliderA = sram_read((int *) 0x1401);
    pSliderVoltage->sliderB = sram_read((int *) 0x1401);

    pJoystickState->isButtonPressedRisingEdge = joystick_detect_button_pressed(0); // TODO: Take button as input

    if(joystick_get_direction_x() != pJoystickState->currentDirectionX)
    {
        pJoystickState->currentDirectionX = joystick_get_direction_x();
    }
    else
    {
        pJoystickState->currentDirectionX;
    }

    if(joystick_get_direction_y() != pJoystickState->currentDirectionY)
    {
        pJoystickState->currentDirectionY = joystick_get_direction_y();
    }
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

int8_t joystick_detect_position(int positionPercentage)
{
    uint8_t threshold=50;
    if(positionPercentage>threshold)
    {
        return 1;
    }
    if(-positionPercentage>threshold)
    {
        return -1;
    }
    return 0;
}

int8_t joystick_detect_button_pressed(int buttonInput)
{
    if(buttonInput)
    {
        return 1;
    }
    return 0;
}

int8_t joystick_get_direction_x()
{
    return joystick_detect_position(get_joystick_angle_x());
}

int8_t joystick_get_direction_y()
{
    return joystick_detect_position(get_joystick_angle_y());
}

void joystick_init()
{
    DDRD &= (0b11111101 << DD1);
}