/* PROJECT NAME AVR_COFFEE_TIMER
 * TARGET       ATMEL ATMEGA328P
 * DATE CREATED 8/12/2020
 * AUTHOR       NICK FRANGOS
 */

#define F_CPU 16000000UL

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "TM1637.h"

extern uint8_t segmap[];

uint16_t ms = 0;
uint8_t sec = 0;
uint8_t min = 0;
uint8_t start_flag = 0;

ISR(TIMER1_COMPA_vect)
{
//  count 999 times in ms counter
    if(start_flag == 0)
    {
        ms = 0;
    }
    else
    {
        if(ms < 999)
        {
            ms++; 
        }
    //  count 1000th time and reset ms counter
        else
        {
            ms = 0;
            sec++;
            if(sec > 59)
            {
                sec=0;
                min++;
            }
            if(min > 99)
            {
                min=0;
                //stop timer
            }
        }
    }
}

int main(void)
{
    char min_buffer[2] = {0};
    char sec_buffer[2] = {0};

    uint8_t b0_state = 0;
    uint8_t b01_state = 0;

    min = (min_buffer[0] - '0') * 10;
    min = min + (min_buffer[1] - '0');
    sec = (sec_buffer[0] - '0') * 10;
    sec = sec + (sec_buffer[1] - '0');
    
    TM_init();
    TM_start();
    TM_send(TM_DISPON);
    TM_stop();
    TM_fillDisplay();
    _delay_ms(500);
    TM_clearDisplay();
    TM_printValue(segmap[(min/10)],segmap[(min%10)],segmap[(sec/10)],segmap[(sec%10)]);
    
    TCCR1B |= (1 << CS10) | (1<<WGM12); // set prescalar to 1
    OCR1A  = 16000; // match 1ms at 16MHZ FCPU
    TIMSK1 |= (1 << OCIE1A);
    sei();
    
    while(1)
    {
        if(sec & 0x01)
        {
            TM_printValue(segmap[(min/10)],segmap[(min%10)]+0x80,segmap[(sec/10)],segmap[(sec%10)]);
        }
        else
        {
            TM_printValue(segmap[(min/10)],segmap[(min%10)],segmap[(sec/10)],segmap[(sec%10)]);
        }
    }
    return 0;
}
