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

void joystick_read(struct JoystickVoltage* pJoystickVoltage);

float joystickVoltageToAngleX(uint8_t voltage);
float joystickVoltageToAngleY(uint8_t voltage);

float joystickVoltageToSlider(uint8_t voltage);


#endif // JOYSTICK_H