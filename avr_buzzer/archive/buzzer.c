/* PROJECT NAME AVR_BUZZER
 * TARGET       ATMEL ATMEGA328P
 * DATE CREATED 6/26/2020
 * AUTHOR       NICK FRANGOS
 */

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRD |= (1 << DDD6);
    TCCR0A |= (1 << COM0A0) | (1 << WGM01) | (1 << WGM00);
    TCCR0B |= (1 << CS01) | (1 << CS00) | (1 << WGM02);
    OCR0A = (0xFF);

    ADMUX |= (1 << ADLAR);
    ADCSRA |= (1 << ADEN);

    uint8_t buzzer_delay = 50;

    while(1){
    _delay_ms(buzzer_delay);
    OCR0A = (OCR0A >> 1);
    _delay_ms(buzzer_delay);
    OCR0A = (OCR0A >> 1);
    _delay_ms(buzzer_delay);
    OCR0A = (OCR0A >> 1);
    _delay_ms(buzzer_delay);
    OCR0A = (OCR0A >> 1);
    _delay_ms(buzzer_delay);
    OCR0A = (0xFF);
    }

    return 0;
}
