#ifndef ENCODER_H
#define ENCODER_H

#include "sam.h"

#define ENCODER_RANGE 5600.0f

void encoder_init();

int encoder_sample();

uint32_t encoder_direction();

#endif // ENCODER_H