/* PROJECT NAME AVR_COFFEE_TIMER 
 * TARGET       ATMEL ATMEGA328P
 * DATE CREATED 7/24/2020
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

    }
    return 0;
}
