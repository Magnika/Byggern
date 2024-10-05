#ifndef JOYSTICK_H
#define JOYSTICK_H

#define F_CPU 8e6// Clock Speed

#include <stdint.h>
#include <stdlib.h>
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

struct JoystickState
{
    uint8_t isButtonPressed;
    uint8_t isJoystickEngagedX;
    uint8_t isJoystickEngagedY;
};
volatile struct JoystickState joystickState;

void joystick_update(struct JoystickVoltage* pJoystickVoltage, struct SliderVoltage* pSliderVoltage, struct JoystickState* pJoystickState);

int get_joystick_angle_x();
int get_joystick_angle_y();

int get_slider_pos(uint8_t voltage);

/**
 * @brief Returns whether the joystick position is exceeding a threshold
 * 
 * @param positionPercentage 
 * @return 1 if is exceeding pos, -1 if exceeding neg
 * @return 0 if is not exceeding
 */
int8_t joystick_detect_position(int positionPercentage);

/**
 * @brief Returns whether the button is pressed
 * 
 * @param buttonInput 
 * @return 1 if is pressed, 0 otherwise 
 */
int8_t joystick_detect_button_pressed(int buttonInput);

/**
 * @brief Return direction of joystick in x direction
 */
int8_t joystick_get_direction_x();

/**
 * @brief Return direction of joystick in y direction
 */
int8_t joystick_get_direction_y();

#endif // JOYSTICK_H