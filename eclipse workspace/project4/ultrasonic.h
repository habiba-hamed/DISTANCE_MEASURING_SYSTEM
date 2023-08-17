/***********************************************************************
 *
 * File name: ultrasonic.h
 *
 * Description: a Header file for ultrasonic sensor driver
 *
 * Created on: Oct 18 , 2021
 *
 * Author: Habiba Hamed
 *
 ***********************************************************************/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define TRIGON PORTB|=(1<<5)
#define TRIGOFF PORTB&= ~(1<<5)

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 *  Initialize the ICU driver to make it detect first the raising edge
 *  Setup the ICU call back function to make it calculate the distance sensed by the ultrasonic sensor
 *  Setup the direction for the trigger pin as output pin through the
    GPIO driver.
 */

void Ultrasonic_init(void);

/*
 * Description :
 *  function to get the high time and store it in a global variable called g_timeHigh
 */
void  Ultrasonic_edgeProcessing(void);

/*
 * Description :
 *  Send the trigger pulse by using Ultrasonic_Trigger function.
 *  Start the measurements by the ICU from this moment.
 */
uint16 Ultrasonic_readDistance(void);

/*
 * Description :
 *  Send the Trigger pulse to the ultrasonic
 */
void Ultrasonic_Trigger(void);



#endif /* ULTRASONIC_H_ */
