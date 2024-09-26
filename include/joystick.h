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

float joystick_voltage_to_angle_x(uint8_t voltage);
float joystick_voltage_to_angle_y(uint8_t voltage);

float joystick_voltage_to_slider(uint8_t voltage);


#endif // JOYSTICK_H