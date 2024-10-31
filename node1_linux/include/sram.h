#ifndef SRAM_H
#define SRAM_H

#include "avr.h"

#define SRAM_START_ADDR 0x1800; // Start address for the SRAM

void SRAM_init();

/**
 * @brief Set the SRE bit in the MCUCR register. This enables the use of external SRAM.'
 * @details Writing SRE to one enables the External Memory Interface.The pin functions AD7:0, A15:8,
    ALE, WR, and RD are activated as the alternate pin functions. The SRE bit overrides any pin
    direction settings in the respective Data Direction Registers. Writing SRE to zero, disables the
    External Memory Interface and the normal pin and data direction settings are used.
 * 
 */
void SRE_bit_enable();

/**
* @brief Activtes pull up  resistors on AD7:0 ports.
* @details The pull-up resistors on the AD7:0 ports may be activated if the corresponding Port register is
    written to one. To reduce power consumption in sleep mode, it is recommended to disable the
    p   ull-ups by writing the Port register to zero before entering sleep.

**/
void AD70_pullup_activate();

/**
 * @brief Reads from some addres
 * @details WARNING, does not neccesariry read from SRAM but some addres that could be OLED or ADC
 * @param addr 
 * @return uint8_t 
 */
uint8_t sram_read(int* addr);

/**
 * @brief Writes to some addres
 * @details WARNING, does not neccesariry write to SRAM but some addres that could be OLED or ADC
 * @param addr 
 * @return uint8_t 
 */
void sram_write(int* addr, uint8_t value);

#endif // SRAM_H