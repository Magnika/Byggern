#ifndef CONTROL_H
#define CONTROL_H

#include <stdint.h>
#include "include/pwm.h"

/**
 * @details pos_target is on the range [0,200]
 */
int pos_control_loop(int pos_target);

#endif // CONTROL_H