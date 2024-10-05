#include "oled.h"
#include "fonts.h"

void oled_cs_test()
{
    volatile char *ext_oled = (char *) 0x1200; // Start address for the OLED
    ext_oled[0] = 69;
}

/**
 * @brief Taken from OLED datasheet
 * 
 */
void oled_init()
{
    oled_write_c(0xae); // display off
    oled_write_c(0xa1); //segment remap
    oled_write_c(0xda); //common pads hardware: alternative
    oled_write_c(0x12);
    oled_write_c(0xc8); //common output scan direction:com63~com0
    oled_write_c(0xa8); //multiplex ration mode:63
    oled_write_c(0x3f);
    oled_write_c(0xd5); //display divide ratio/osc. freq. mode
    oled_write_c(0x80);
    oled_write_c(0x81); //contrast control
    oled_write_c(0x50);
    oled_write_c(0xd9); //set pre-charge period
    oled_write_c(0x21);
    oled_write_c(0x20); //Set Memory Addressing Mode
    oled_write_c(0x02);
    oled_write_c(0xdb); //VCOM deselect level mode
    oled_write_c(0x30);
    oled_write_c(0xad); //master configuration
    oled_write_c(0x00);
    oled_write_c(0xa4); //out follows RAM content
    oled_write_c(0xa6); //set normal display
    oled_write_c(0xaf); // display on

    for(uint8_t i=0; i<OLED_NUM_PAGES; i++)
    {
        for(uint8_t j=0; j<OLED_NUM_COLUMNS; j++)
        {
            oled_printf(" ", i, j);
        }
    }
}

/**
 * @brief Write command to OLED
 * 
 * @param c 8-bit command
 */
void oled_write_c(char c)
{
    volatile char *ext_oled_command = (char *) 0x1000; // Start address for the OLED command memory space
    ext_oled_command[0] = c;
}

/**
 * @brief Write data to OLED
 * 
 * @param c 8-bit command
 */
void oled_write_d(char data)
{
    volatile char *ext_oled_data = (char *) 0x1200; // Start address for the OLED command memory space

    const unsigned char* code = &(font8[data-ASCII_TABLE_OFFSET][0]);
    for(uint8_t i=0; i<8; i++)
    {
        uint8_t byte = pgm_read_byte(&(code[i]));
        ext_oled_data[0] = byte;
    }
}

void oled_printf(char* string, int page, int column)
{
    oled_write_c(0xa4);
    int length = strlen(string);

    // Set page and column to write
    oled_write_c(0x21);
    oled_write_c(column);
    oled_write_c(0x7F);

    oled_write_c(0x22);
    oled_write_c(page);
    oled_write_c(0xF);
    
    for (int i = 0; i < length; i++)
    {
        oled_write_d(string[i]);
    }
    
}

void oled_print_menu()
{
    oled_write_c(0xa4);
    oled_printf("Menu", 0, 50);
    oled_printf("~~~~", 2, 50);
    oled_printf("Option 1", 4, 40);
    oled_printf("Option 2", 5, 40);
    oled_printf("Option 3", 6, 40);
}

void oled_print_cursor_at_option(uint8_t option_nr)
{
    uint8_t option_page_base = 4;
    uint8_t option_column_nr = 112;
    oled_write_c(0xa4);
    oled_printf("<-", option_page_base+(option_nr-1), option_column_nr);
}

void oled_clear_cursor()
{
    uint8_t option_column_nr = 112;

    oled_write_c(0xa4);
    for(uint8_t i=0; i<OLED_NUM_PAGES; i++)
    {
        oled_printf("  ", i, option_column_nr);
    }
}
