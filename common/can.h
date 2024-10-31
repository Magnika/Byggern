#ifndef CAN_H
#define CAN_H

#include <stdint.h>

#define SMP 0x1
#define PHASE1 0x50
#define PHASE2 0x6
#define PROPAG 0x100
#define SJW 0x3000
#define BRP 0x140000
#define SMP 0x1000000
#define CAN_BR_SETTINGS (SMP | BRP | SJW | PROPAG | PHASE1 | PHASE2)

typedef struct
{
    uint16_t id;
    char data_length;
    char data[8];
} can_frame_t;

void can_init();

void can_transmit(can_frame_t* msg);

void can_read(can_frame_t* msg);

#endif // CAN_H