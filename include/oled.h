#ifndef OLED_H
#define OLED_H

#include <stdint.h>

void oled_cs_test();
void oled_init();
void oled_write(uint8_t dataOrCommand, char address);
void oled_write_c(char c);
void oled_write_d(char data);

#endif // OLED_H