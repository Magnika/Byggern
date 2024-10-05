#include "oled.h"
#include "fonts.h"

void oled_cs_test()
{
    volatile char *ext_oled = (char *) 0x1200; // Start address for the OLED
    ext_oled[0] = 69;
}

void oled_print_char_test()
{
    char test = 'A';
    //oled_write_c(0x40);
    oled_write_d(test, 0, 0);
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
}

void oled_write(uint8_t dataOrCommand, char address)
{
    // Set address

    // Write enable (should be automatic, but check)

    // Send data on data bus


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
void oled_write_d(char data, uint8_t page, uint8_t column)
{
    volatile char *ext_oled_data = (char *) 0x1200; // Start address for the OLED command memory space

    // Set page and column to write
    oled_write_c(0x21);
    oled_write_c(column);
    oled_write_c(0x7F);

    oled_write_c(0x22);
    oled_write_c(page);
    oled_write_c(0xF);

    const unsigned char* code = font8[data-ASCII_TABLE_OFFSET];
    for(uint8_t i=0; i<8; i++)
    {
        uint8_t byte = pgm_read_byte(&(code[i]));
        ext_oled_data[0] = code[i];
        _delay_us(1);
    }
}