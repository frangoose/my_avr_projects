/* PROJECT NAME TM1637_clock
 * TARGET       ATMEL ATMEGA328P
 * DATE CREATED 5/21/2020
 * AUTHOR       NICK FRANGOS
 */

#define F_CPU 16000000UL

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "TM1637.h"
#include "USART.h"

extern uint8_t segmap[];

uint16_t ms = 0;
uint8_t sec = 0;
uint8_t min = 0;
uint8_t hr = 0;
uint8_t print_flag = 0;

ISR(TIMER1_COMPA_vect)
{
//  count 999 times in ms counter
    if(ms < 999)
    {
        ms++; 
    }
//  count 1000th time and reset ms counter
    else
    {
        ms = 0;
        sec++;
        print_flag = 1;
        if(sec > 59)
        {
            sec=0;
            min++;
        }
        if(min > 59)
        {
            min=0;
            hr++;
        }
        if(hr > 12)
        {
            hr=1;
        }
    }
}

int main(void)
{
    USART_Init(9600);
    char hr_buffer[2];
    char min_buffer[2];
    char sec_buffer[2];

    for(uint8_t i = 0; i < 2; i++)
    {
        hr_buffer[i] = USART_Receive();
    }
    for(uint8_t i = 0; i < 2; i++)
    {
        min_buffer[i] = USART_Receive();
    }
    for(uint8_t i = 0; i < 2; i++)
    {
        sec_buffer[i] = USART_Receive();
    }

    hr = (hr_buffer[0] - '0') * 10;
    hr = hr + (hr_buffer[1] - '0');
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
    TM_printValue(segmap[(hr/10)],segmap[(hr%10)],segmap[(min/10)],segmap[(min%10)]);
    
    TCCR1B |= (1 << CS10) | (1<<WGM12); // set prescalar to 1
    OCR1A  = 16000; // match 1ms at 16MHZ FCPU
    TIMSK1 |= (1 << OCIE1A);
    sei();
    
    while(1)
    {
        if(sec & 0x01)
        {
            TM_printValue(segmap[(hr/10)],segmap[(hr%10)]+0x80,segmap[(min/10)],segmap[(min%10)]);
        }
        else
        {
            TM_printValue(segmap[(hr/10)],segmap[(hr%10)],segmap[(min/10)],segmap[(min%10)]);
        }
        if(print_flag)
        {
            USART_Transmit((hr/10) + '0');
            USART_Transmit((hr%10) + '0');
            USART_Transmit(':');
            USART_Transmit((min/10) + '0');
            USART_Transmit((min%10) + '0');
            USART_Transmit(':');
            USART_Transmit((sec/10) + '0');
            USART_Transmit((sec%10) + '0');
            USART_Transmit('\r');
            USART_Transmit('\n');
            print_flag = 0;
        }
    }
    return 0;
}
