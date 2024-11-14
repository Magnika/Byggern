#include "include/control.h"
#include "include/encoder.h"
#include "include/uart.h"

int pos_control_loop(int pos_target)
{
    static float e_int = 0;
    static float dt = 0.020; // 50 Hz loop
    static int Kp=3;
    static float Ki=0.001;

    int pos_meas = encoder_sample();
    int pos_relative_percent = 100* pos_meas/ENCODER_RANGE;
    int target_relative = pos_target/2;

    int e = target_relative - pos_relative_percent;
    e_int += (float) (target_relative-pos_relative_percent)*dt;

    int u = Kp*e + Ki*e_int;
    
    pwm_motor_set_duty_cycle(u);
    
    if(u>0)
    {
        pwm_motor_set_duty_cycle(u);
        pwm_set_motor_direction(-1);
    }
    else
    {
        pwm_motor_set_duty_cycle(-u);
        pwm_set_motor_direction(1);
    }

    //printf("%d  |  %d\n\r", target_relative, pos_relative_percent);
    //printf("Error=%d\n\r",e);
    //printf("e_int=%f\n\r",e_int);

    return u;
}