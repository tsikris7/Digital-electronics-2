/***********************************************************************
 * 
 * Seven-segment display library for AVR-GCC.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2019-Present Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 *
 **********************************************************************/

/* Includes ----------------------------------------------------------*/
#ifndef F_CPU
# define F_CPU 16000000
#endif
#include <util/delay.h>
#include "gpio.h"
#include "segment.h"

uint8_t segment_value[] = {
    // abcdefgDP
    0b00000011,     // Digit 0
    0b10011111,          // Digit 1
    0b00100101,          // Digit 2
    0b00001101,     // Digit 3
    0b10011001,          // 4
    0b01001001,         // 5
    0b01000001,       //6
    0b00011111,         //7
    0b00000001,      //8
    0b00001001,       //9
};
uint8_t segment_position[] = {
    0b00010000
    0b00100000
    0b01000000
    0b10000000

/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: SEG_init()
 * Purpose:  Configure SSD signals LATCH, CLK, and DATA as output.
 * Returns:  none
 **********************************************************************/
void SEG_init(void)
{
    /* Configuration of SSD signals */
    GPIO_config_output(&DDRD, SEG_LATCH);
    GPIO_config_output(&DDRD, SEG_CLK);
    GPIO_config_output(&DDRB, SEG_DATA);
}

/**********************************************************************
 * Function: SEG_update_shift_regs()
 * Purpose:  Display segments at one position of the SSD.
 * Input:    segments - Segments to be displayed (abcdefgDP, active low)
 *           position - Position of the display where the segments are to 
 *                      be displayed (p3 p2 p1 p0 xxxx, active high)
 * Returns:  none
 **********************************************************************/
void SEG_update_shift_regs(8,3)
{
    uint8_t bit_number;
    segments=segment_value[segments];
    positions=segment_position[position];
    
    

    // Pull LATCH, CLK, and DATA low
 GPIO_write_low(&PORTD, SEG_LATCH);
 GPIO_write_low(&PORTD, SEG_CLK);
 GPIO_write_low(&PORTB, SEG_DATA);
 
    // Wait 1 us

    // Loop through the 1st byte (segments)
    // a b c d e f g DP (active low values)
    for (bit_number = 0; bit_number < 8; bit_number++)
    {
        // Test LSB of "segments" by & (faster) or % (slower) and... 
        // ...output DATA value

        // Wait 1 us
_delay_us()
        // Pull CLK high
GPIO_write_high(&PORTD, SEG_CLK);
        // Wait 1 us
_delay_us()
        // Pull CLK low
GPIO_write_low(&PORTD, SEG_CLK);
        // Shift "segments"
        segments = segments >> 1;
    }

    // Loop through the 2nd byte (position)
    // p3 p2 p1 p0 . . . . (active high values)
    for (bit_number = 0; bit_number < 8; bit_number++)
    {
        // Test LSB of "position" by & (faster) or % (slower) and... 
        // ...output DATA value
        if((position & 1) == 0)
           GPIO_write_low(&PORTB, SEG_DATA);
           else
           GPIO_write_high(&PORTB, SEG_DATA);
        // Wait 1 us
_delay_us(1)

        // Pull CLK high
GPIO_write_high(&PORTB, SEG_CLK);
        // Wait 1 us
_delay_us(1)
        // Pull CLK low
GPIO_write_low(&PORTB, SEG_CLK);
        // Shift "position"
        position = position >> 1;
    }

    // Pull LATCH high
GPIO_write_high(&PORTD, SEG_LATCH);
    // Wait 1 us
_delay_us(1)
}

/**********************************************************************
 * Function: SEG_clear()
 **********************************************************************/

/**********************************************************************
 * Function: SEG_clk_2us()
 **********************************************************************/