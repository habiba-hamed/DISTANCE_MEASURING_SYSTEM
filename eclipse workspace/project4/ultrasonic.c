/***********************************************************************
 *
 * File name: ultrasonic.c
 *
 * Description: a source file for ultrasonic sensor driver
 *
 * Created on: Oct 18 , 2021
 *
 * Author: Habiba Hamed
 *
 ************************************************************************/
#include "ultrasonic.h"
#include "common_macros.h"
#include "icu.h"
#include "gpio.h"
#include <avr/io.h> /* To use the SREG register */
#include <util/delay.h>

/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/
uint8 g_edgeCount = 0;
uint16 g_timeHigh = 0;

/*
 * Description :
 * function to get the high time and store it in a global variable called g_timeHigh
 */
void  Ultrasonic_edgeProcessing(void)
{
	g_edgeCount++;
	if(g_edgeCount == 1)
	{
		/*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */
		Icu_clearTimerValue();
		/* Detect falling edge */
		Icu_setEdgeDetectionType(FALLING);
	}
	else if(g_edgeCount == 2)
	{
		/* Store the High time value */
		g_timeHigh = Icu_getInputCaptureValue();
		/* Detect rising edge */
		Icu_setEdgeDetectionType(RISING);
		g_edgeCount=0;
	}

}

/*
 * Description :
 * Initialize the ICU driver to make it detect first the raising edge with frequency FCPU/8.
 * Setup the ICU call back function to make it calculate the distance sensed by the ultrasonic sensor.
 * Setup the direction for the trigger pin as output pin through the
GPIO driver.
 */
void Ultrasonic_init(void){
	/* Create configuration structure for ICU driver */
	Icu_ConfigType Icu_Config = {F_CPU_8,RISING};
	/* Initialize the ICU driver */
	Icu_init(&Icu_Config);
	/*Setup the direction for the trigger pin as output pin through the
			GPIO driver.*/
	GPIO_setupPinDirection(PORTB_ID, PIN5_ID, PIN_OUTPUT);

	/* Set the Call back function pointer in the ICU driver */
	Icu_setCallBack(Ultrasonic_edgeProcessing);
	TRIGOFF; /* initially set trig pin off */


}



/*
 * Description :
 *  Send the Trigger pulse to the ultrasonic
 */
void Ultrasonic_Trigger(void){
	TRIGON;
	_delay_us(10);
	TRIGOFF;
}
/*
 * Description :
 *  Send the trigger pulse by using Ultrasonic_Trigger function.
 *  Start the measurements by the ICU from this moment.
 */
uint16 Ultrasonic_readDistance(void){
	uint16 distance =0;
	Ultrasonic_Trigger();
	distance = g_timeHigh/(58.8);
	return distance;
}

