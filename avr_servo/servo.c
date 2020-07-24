/* PROJECT NAME AVR_SERVO
*  TARGET       ATMEL ATMEGA328P
*  DATE CREATED 7/10/2020
*  AUTHOR       NICK FRANGOS
*/

#define F_CPU 16000000UL
#define SERVO_MIN 950
#define SERVO_MAX 4900

#include <avr/io.h>
#include <util/delay.h>

void SERVO_sweep(void);

int main(void)
{
    TCCR1A |= (1 << COM1A1) | (1 << COM1A0) | (1 << WGM11); 
    TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11);
    ICR1 = 40000; // 16MHZ FCPU with prescalar 8 takes 40k cycles to achieve 50HZ
    OCR1A = SERVO_MAX/2;

    DDRB = 0xFF;

    while(1)
    {
        SERVO_sweep();
    }

    return 0;
}

void SERVO_sweep(void){
        uint16_t duty = 2450;
        OCR1A = ICR1 - duty;
        _delay_ms(500);
        duty = 2450 + 1250;
        OCR1A = ICR1 - duty;
        _delay_ms(500);
        duty = 2450;
        OCR1A = ICR1 - duty;
        _delay_ms(500);
        duty = 2450 - 1250;
        OCR1A = ICR1 - duty;
        _delay_ms(500);
}
