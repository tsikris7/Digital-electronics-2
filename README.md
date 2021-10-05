# Digital-electronics-2
1.What is the meaning of the following binary operators in C?
   * `|`=OR
   * `&`=AND
   * `^`=XOR
   * `~`=(tilde) inversion of a bit
   * `<<`=shift left operator
   * `>>`=shift right operator
   *
   * 
   *   2. Complete truth table with operators: `|`, `&`, `^`, `~`

| **b** | **a** |**b or a** | **b and a** | **b xor a** | **not b** |
| :-: | :-: | :-: | :-: | :-: | :-: |
| 0 | 0 | 0 | 0 | 0 | 1 |
| 0 | 1 | 1 | 1 | 1 | 0 |
| 1 | 0 | 1 | 1 | 1 | 1 |
| 1 | 1 | 1 | 1 | 0 | 0 |


### Morse code
#define LED_GREEN   PB5
#define SHORT_DELAY 1000
#define SHORT_DELAY1 3000
#define SHORT_DELAY2 250
#ifndef F_CPU 
# define F_CPU 16000000 
#endif 
#include <until/delay.h>
#include <avr/io.h>

int main(void)
{
    // Set pin as output in Data Direction Register
    // DDRB = DDRB or 0010 0000
    DDRB = DDRB | (1<<LED_GREEN);

    // Set pin LOW in Data Register (LED off)
    // PORTB = PORTB and 1101 1111
    PORTB = PORTB & ~(1<<LED_GREEN);

    // Infinite loop
    while (1)
    {
        PORTB = PORTB ^ (1<<LED_GREEN);
        _delay_ms(SHORT_DELAY);
        PORTB = PORTB ^ (1<<LED_GREEN);
        _delay_ms(SHORT_DELAY2);
        PORTB = PORTB ^ (1<<LED_GREEN);
        _delay_ms(SHORT_DELAY1);
        
        
    }

    // Will never reach this
    return 0;
}

![244077510_840440159989425_5401950173975616363_n](https://user-images.githubusercontent.com/91612206/136067704-c1881256-f219-432d-a121-3237591e55ad.png)
