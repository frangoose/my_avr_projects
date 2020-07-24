//Version 1.0
//11/2/19

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "Snake.h"

int main(void)
{
	SPI_MasterInit();
	NOKIA_Init();
	Timer1_CTC_Init();
	Direction dir = RIGHT;
	while (1)
    {
		Snake_Init(dir, 10); //start direction, start length
		
		while(!Snake_Contact())
		{
			if(Snake_Eat_Apple())
			{
				Snake_Grow(dir);
				Snake_Move(dir);
			}
			else
			{
				Snake_Move(dir);
			}
			NOKIA_Update_Display();
			_delay_ms(50); //refresh rate
		}
		Snake_End();
		Snake_ChangeDir(&dir);
	}
}


ISR(TIMER1_COMPA_vect)
{

}