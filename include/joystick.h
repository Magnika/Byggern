#ifndef JOYSTICK_H
#define JOYSTICK_H

#define F_CPU 8e6// Clock Speed

#include <stdint.h>;
#include "sram.h"
#include <util/delay.h>

struct JoystickVoltage
{
    uint8_t xValue;
    uint8_t yValue;
};
volatile struct JoystickVoltage joystickVoltage;

struct SliderVoltage
{
    uint8_t sliderA;
    uint8_t sliderB;
};
volatile struct SliderVoltage sliderVoltage;

void joystick_read(struct JoystickVoltage* pJoystickVoltage, struct SliderVoltage* pSliderVoltage);

int get_joystick_angle_x();
int get_joystick_angle_y();

int get_slider_pos(uint8_t voltage);


#endif // JOYSTICK_H