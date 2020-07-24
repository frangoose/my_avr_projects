/* PROJECT NAME AVR_SYNTH
 * TARGET       ATMEL ATMEGA328P
 * DATE CREATED 6/26/2020
 * AUTHOR       NICK FRANGOS
 */

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

#include "pitches.h"
#include "buzzer.h"
#include "TM1637.h"

#define BZR_DDR DDRD
#define BZR_PORT PORTD
#define BZR_PIN PIND
#define BZR_BUTTON0 4
#define BZR_BUTTON1 5
#define BZR_BUTTON2 6
#define BZR_BUTTON3 7

extern uint8_t segmap[];

int main(void)
{
    TM_init();
    TM_start();
    TM_send(TM_DISPON);
    TM_stop();
    TM_clearDisplay();

    BZR_init();

    BZR_DDR &= ~(1 << BZR_BUTTON0);
    BZR_DDR &= ~(1 << BZR_BUTTON1);
    BZR_DDR &= ~(1 << BZR_BUTTON2);
    BZR_DDR &= ~(1 << BZR_BUTTON3);
    BZR_PORT |= (1 << BZR_BUTTON0) | (1 << BZR_BUTTON1) | (1 << BZR_BUTTON2) | (1 << BZR_BUTTON3); 
    ADMUX |= (1 << ADLAR);
    ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);

    uint8_t adc_data;
    uint8_t adc_data_raw;
    uint8_t button0;
    uint8_t button1;
    uint8_t button2;
    uint8_t button3;

    while(1){
        button0 = ((BZR_PIN & (1 << BZR_BUTTON0)) >> BZR_BUTTON0);
        button1 = ((BZR_PIN & (1 << BZR_BUTTON1)) >> BZR_BUTTON1);
        button2 = ((BZR_PIN & (1 << BZR_BUTTON2)) >> BZR_BUTTON2);
        button3 = ((BZR_PIN & (1 << BZR_BUTTON3)) >> BZR_BUTTON3);
        adc_data_raw = ADCH;
        adc_data = adc_data_raw >> 2;
        TM_printValue(segmap[0], segmap[(adc_data_raw / 100)], segmap[(adc_data_raw / 10) % 10], segmap[(adc_data_raw) % 10]);

        if(!button0)
        {
            OCR1A = (E3 + adc_data);
        }
        else if(!button1)
        {
            OCR1A = (E4 + adc_data);
        }
        else if(!button2)
        {
            OCR1A = (E5 + adc_data);
        }
        else if(!button3)
        {
            OCR1A = (E6 + adc_data);
        }
        else
        {
            OCR1A = 0x0001;
        }
    }

    return 0;
}
