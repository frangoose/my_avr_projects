/* PROJECT NAME AVR_BUZZER
 * TARGET       ATMEL ATMEGA328P
 * DATE CREATED 6/26/2020
 * AUTHOR       NICK FRANGOS
 */

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "pitches.h"

#define TEMPO 190
#define ENOTE ((60000/TEMPO))/2
#define QNOTE ((60000/TEMPO))
#define HNOTE ((60000/TEMPO))*2
#define WNOTE ((60000/TEMPO))*4

void play_note(uint16_t pitch, uint16_t duration);
void play_mario(void);

int main(void)
{
    DDRB |= (1 << DDB1);
    TCCR1A |= (1 << COM1A0) | (1 << WGM10);
    TCCR1B |= (1 << CS11) | (1 << CS10) | (1 << WGM13);
    OCR1A = (0x0000);

    uint8_t adc_data;
    
    ADMUX |= (1 << ADLAR);
    ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);

    while(1){
        adc_data = ADCH;
        OCR1A = E6 + adc_data;
    }

    return 0;
}


void play_note(uint16_t pitch, uint16_t duration)
{
    OCR1A = (pitch);
    for(int i = 0; i < duration; i++)
    {
        _delay_ms(1);
    }
    OCR1A = (0x0001);
    _delay_ms(50);
}

void play_mario(void)
{
        play_note(E6, ENOTE);
        play_note(E6, QNOTE);
        play_note(E6, QNOTE);
        play_note(C6, ENOTE);
        play_note(E6, QNOTE);
        play_note(G6, HNOTE);
        play_note(G5, HNOTE);
        play_note(0x0001, 1000);
}
