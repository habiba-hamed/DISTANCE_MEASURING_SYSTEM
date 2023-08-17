/***********************************************************************
 *
 * File name: application.c
 *
 * Description: a source file for application which measures the distance using ultrasonic sensor
 *
 * Created on: Oct 18 , 2021
 *
 * Author: Habiba Hamed
 *
 ***********************************************************************/
#include "std_types.h"
#include "lcd.h"
#include "ultrasonic.h"
#include <avr/io.h>

int main(){
	uint16 distance=0;
	LCD_init(); /* Initialize the LCD */
	LCD_displayString("Distance =");
	LCD_moveCursor(0,13);
	LCD_displayString(" cm");
	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);
	Ultrasonic_init();
	while (1){
		/*add 2 to the measured distance to reduce the error */
		distance=Ultrasonic_readDistance()+2;
		/* Display the distance value every time at same position */
		LCD_moveCursor(0,10);
		if(distance >= 100)
		{
			LCD_intgerToString(distance);
		}
		else
		{

			LCD_intgerToString(distance);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');

		}
	}
}




