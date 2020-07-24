/* PROJECT NAME AVR_BLINK
 * TARGET       ATMEL ATMEGA328P
 * DATE CREATED 5/9/2020
 * AUTHOR       NICK FRANGOS
 */

#define F_CPU 16000000UL
#define BLINK_DELAY 1000

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRB |= (1<<DDB5);
    while(1)
    {
        PORTB |= (1<<PORTB5);
        _delay_ms(BLINK_DELAY);
        PORTB &= ~(1<<PORTB5);
        _delay_ms(BLINK_DELAY);
    }
    return 0;
}
