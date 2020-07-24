//Version 1.0
//11/23/19

#include "Timer.h"

void Timer1_CTC_Init(void)
{
	TCCR1A |= (1<<COM1A0);
	TCCR1B |= (1<<WGM12) | (1<<CS11);
	TIMSK1 |= (1<<OCIE1A);
	OCR1A = 0xFFFF/4;
	sei();
}
