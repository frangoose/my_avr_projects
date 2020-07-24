/* PROJECT NAME AVR_BUZZER
 * TARGET       ATMEL ATMEGA328P
 * DATE CREATED 6/26/2020
 * AUTHOR       NICK FRANGOS
 */

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "pitches.h"

int main(void)
{
    DDRB |= (1 << DDB1);
    TCCR1A |= (1 << COM1A0) | (1 << WGM10);
    TCCR1B |= (1 << CS11) | (1 << CS10) | (1 << WGM13);
    OCR1A = (0x0000);

    while(1){
        _delay_ms(25);
        OCR1A = (A2);
        _delay_ms(25);
        OCR1A = (A3);
        _delay_ms(25);
        OCR1A = (A4);
        _delay_ms(25);
        OCR1A = (A5);
        _delay_ms(25);
        OCR1A = (A6);

        _delay_ms(25);
        OCR1A = (B2);
        _delay_ms(25);
        OCR1A = (B3);
        _delay_ms(25);
        OCR1A = (B4);
        _delay_ms(25);
        OCR1A = (B5);
        _delay_ms(25);
        OCR1A = (B6);

        _delay_ms(25);
        OCR1A = (C3);
        _delay_ms(25);
        OCR1A = (C4);
        _delay_ms(25);
        OCR1A = (C5);
        _delay_ms(25);
        OCR1A = (C6);
        _delay_ms(25);
        OCR1A = (C7);

        _delay_ms(25);
        OCR1A = (D3);
        _delay_ms(25);
        OCR1A = (D4);
        _delay_ms(25);
        OCR1A = (D5);
        _delay_ms(25);
        OCR1A = (D6);
        _delay_ms(25);
        OCR1A = (D7);
        
        _delay_ms(25);
        OCR1A = (E3);
        _delay_ms(25);
        OCR1A = (E4);
        _delay_ms(25);
        OCR1A = (E5);
        _delay_ms(25);
        OCR1A = (E6);
        _delay_ms(25);
        OCR1A = (E7);
        
        _delay_ms(25);
        OCR1A = (F3);
        _delay_ms(25);
        OCR1A = (F4);
        _delay_ms(25);
        OCR1A = (F5);
        _delay_ms(25);
        OCR1A = (F6);
        _delay_ms(25);
        OCR1A = (F7);

        _delay_ms(25);
        OCR1A = (G3);
        _delay_ms(25);
        OCR1A = (G4);
        _delay_ms(25);
        OCR1A = (G5);
        _delay_ms(25);
        OCR1A = (G6);
        _delay_ms(25);
        OCR1A = (G7);
    }

    return 0;
}
