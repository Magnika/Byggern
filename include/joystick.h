#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <stdint.h>;
#include "adc.h";

struct JoystickVoltage
{
    uint8_t xValue = 0;
    uint8_t yvalue = 0;
};
volatile struct JoystickVoltage joystickVoltage;

struct SliderVoltage
{
    uint8_t sliderA = 0;
    uint8_t sliderB = 0;
};
volatile struct SliderVoltage sliderVoltage;

void readFromADC(struct JoystickVoltage* pJoystickVoltage);

float joystickVoltageToAngleX(uint8_t voltage);
float joystickVoltageToAngleY(uint8_t voltage);

float joystickVoltageToSlider(uint8_t voltage);


#endif // JOYSTICK_H