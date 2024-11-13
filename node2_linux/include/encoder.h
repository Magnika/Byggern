#ifndef ENCODER_H
#define ENCODER_H

#include "sam.h"

void encoder_init();

uint32_t encoder_sample();

uint32_t encoder_direction();

#endif // ENCODER_H