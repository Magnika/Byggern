#ifndef OLED_H
#define OLED_H

#include <stdint.h>
#include <util/delay.h>
#include <string.h>

#define ASCII_TABLE_OFFSET 32
#define OLED_NUM_PAGES 8
#define OLED_NUM_COLUMNS 128

void oled_cs_test();
void oled_init();
void oled_write(uint8_t dataOrCommand, char address);
void oled_write_c(char c);
void oled_write_d(char data);
void oled_print_char_test();

void oled_printf(char* string, int page, int column);

void oled_print_menu();

/**
 * @brief Clears the entire display
 * 
 */
void oled_clear_display();

#endif // OLED_H