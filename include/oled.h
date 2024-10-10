#ifndef OLED_H
#define OLED_H

#include <stdint.h>
#include <util/delay.h>
#include <string.h>

#define ASCII_TABLE_OFFSET 32
#define OLED_NUM_PAGES 8
#define OLED_NUM_COLUMNS 128

/**
 * @brief Test the OLED CS signal, must use scope
 * 
 */
void oled_cs_test();

/**
 * @brief Sends a series of datasheet recommended commands to the oled
 * 
 */
void oled_init();

/**
 * @brief Write a single command to the OLED
 * 
 * @param c 
 */
void oled_write_c(char c);

/**
 * @brief Write a single byte of data to the OLED
 * 
 * @param data 
 */
void oled_write_d(char data);

/**
 * @brief Print a string to the OLED at a determined starting page and column
 * 
 * @param string 
 * @param page 
 * @param column 
 */
void oled_printf(char* string, int page, int column);

/**
 * @brief Print the application main menu on the OLED
 * 
 */
void oled_print_menu();

/**
 * @brief Clears the entire display
 * 
 */
void oled_clear_display();

/**
 * @brief Prints a cursor at the designated option
 * 
 * @param option_nr 
 */
void oled_print_cursor_at_option(uint8_t option_nr);

/**
 * @brief Clears all pages for cursors. NOTE: does not check that in menu!!
 * 
 */
void oled_clear_cursor();

#endif // OLED_H