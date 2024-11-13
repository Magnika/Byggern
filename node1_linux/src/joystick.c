#include "joystick.h"
#include "can_node1.h"

void joystick_update(struct JoystickVoltage* pJoystickVoltage, struct SliderVoltage* pSliderVoltage, struct JoystickState* pJoystickState)
{
    sram_write((int *) 0x1401, (uint8_t) 0b0);
    _delay_us(300);
    pJoystickVoltage->xValue = sram_read((int *) 0x1401);
    pJoystickVoltage->yValue = sram_read((int *) 0x1401);
    pSliderVoltage->sliderA = sram_read((int *) 0x1401);
    pSliderVoltage->sliderB = sram_read((int *) 0x1401);

    pJoystickState->isButtonPressed = joystick_detect_button_pressed((PIND & (1<<PD1)));

    pJoystickState->isJoystickActuatedX = joystick_detect_actuation(get_joystick_angle_x());
    pJoystickState->isJoystickActuatedY = joystick_detect_actuation(get_joystick_angle_y());

    // If state is_actuated and not state is_actuated_prev, then is_rising_edge
    // If joystick is not actuated and state is_actuated_prev, then is_falling_edge

    if(pJoystickState->isJoystickActuatedX==-1 && !(pJoystickState->isJoystickActuatedXPrev==pJoystickState->isJoystickActuatedX))
    {
        pJoystickState->isJoystickActuatedXRisingEdge = -1;
    }
    else if(pJoystickState->isJoystickActuatedX==1 && !(pJoystickState->isJoystickActuatedXPrev==pJoystickState->isJoystickActuatedX))
    {
        pJoystickState->isJoystickActuatedXRisingEdge = 1;
    }
    else
    {
        pJoystickState->isJoystickActuatedXRisingEdge = 0;
    }

    if(pJoystickState->isJoystickActuatedY==1 && !(pJoystickState->isJoystickActuatedYPrev==pJoystickState->isJoystickActuatedY))
    {
        pJoystickState->isJoystickActuatedYRisingEdge = 1;
    }
    else if(pJoystickState->isJoystickActuatedY==-1 && !(pJoystickState->isJoystickActuatedYPrev==pJoystickState->isJoystickActuatedY))
    {
        pJoystickState->isJoystickActuatedYRisingEdge = -1;
    }
    else
    {
        pJoystickState->isJoystickActuatedYRisingEdge = 0;
    }

    if(pJoystickState->isButtonPressed && !pJoystickState->isButtonPressedPrev)
    {
        pJoystickState->isButtonPressedRisingEdge = 1;
    }
    else
    {
        pJoystickState->isButtonPressedRisingEdge = 0;
    }

    pJoystickState->isJoystickActuatedXPrev = pJoystickState->isJoystickActuatedX;
    pJoystickState->isJoystickActuatedYPrev = pJoystickState->isJoystickActuatedY;
    pJoystickState->isButtonPressedPrev = pJoystickState->isButtonPressed;
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

int joystick_detect_actuation(int positionPercentage)
{
    int threshold=50;
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
    return joystick_detect_actuation(get_joystick_angle_x());
}

int8_t joystick_get_direction_y()
{
    return joystick_detect_actuation(get_joystick_angle_y());
}

void joystick_init()
{
    DDRD &= (0b11111101 << DD1);
}

void joystick_transmit_position_over_can()
{
    int angle_x_mapped = get_joystick_angle_x() + 100;
    int angle_y_mapped = get_joystick_angle_y() + 100;
    int isButtonPushed = joystickState.isButtonPressedRisingEdge;

    can_frame_t msg;
    msg.id = 1;
    msg.data[0] = (uint8_t) angle_x_mapped;
    msg.data[1] = (uint8_t) angle_y_mapped;
    msg.data[2] = (uint8_t) isButtonPushed;
    msg.data_length = 3;
    
    can_transmit(&msg);
}