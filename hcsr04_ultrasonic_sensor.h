/******************************************************************************
 *
 * Module: Ultrasonic Sensor (HCSR04)
 *
 * File Name: hcsr04_ultrasonic_sensor.h
 *
 * Description: Header file for the Ultrasonic sensor driver
 *
 * Author: Hazem Montasser
 *
 *******************************************************************************/
#ifndef HCSR04_ULTRASONIC_SENSOR_H_
#define HCSR04_ULTRASONIC_SENSOR_H_
#include "std_types.h"	/* To use uint8, etc...*/
#include "gpio.h"		/* For port & pin definitions */
#include "icu.h"		/* For timer pre-scaler definitions */
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define HCSR04_PULSE_DURATION_US (10U)
#define HCSR04_SOUND_AIR_VELOCITY (340U)
#define HCSR04_TRIGGER_PORT PORTD_ID
#define HCSR04_TRIGGER_PIN PIN5_ID
#define ULTRASONIC_ICU_PRESCALER F_CPU_8

#define HCSR04_DISTANCE_CONSTANT (((HCSR04_SOUND_AIR_VELOCITY*100.0)*(8.0/F_CPU))/2)
#define HCSR04_DISTANCE_CONSTANT_OPTIMIZED (59U)	/* For optimization's sake, saves around 20 operations*/
/* V = d/t
 * Vair = 340 m/s
 * t = T2-T1 = (prescaler/F_CPU) * (Timer value) us = ... * (10^-6) s
 *
 * d = V * t  =
 *
 * (340 * 100)cm/s * (t * 10^(-6))
 * -------------------------------
 *                 2 <----
 *                  	 |
 *                 Because sound wave traveled the
 *                 same distance twice (From emitter to receiver)
 * */

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/******************************************************************************
 *
 * Function Name: Ultrasonic_init
 *
 * Description:  Initializes the ultrasonic sensor i/o pins & calls
 * 				ICU_init to initialize it as well then sets a callback function.
 *
 * Args: void
 * Returns: void
 *******************************************************************************/
void Ultrasonic_init(void);

/******************************************************************************
 *
 * Function Name: Ultrasonic_edgeProcessing (CALLBACK FUNCTION)
 *
 * Description:  Callback function that is called once ICU ISR is executed,
 * 			handles counting of rising & falling edges to calculate a step duration.
 * Args: void
 * Returns: void
 *******************************************************************************/
void Ultrasonic_edgeProcessing(void);

/******************************************************************************
 *
 * Function Name: Ultrasonic_Trigger
 *
 * Description: Sends the trigger pulse to the sensor trigger pin.
 * Args: void
 * Returns: void
 *******************************************************************************/
void Ultrasonic_Trigger(void);

/******************************************************************************
 *
 * Function Name: Ultrasonic_readDistance
 *
 * Description: Sends trigger to the sensor and calculates the distance in cm.
 * Args: void
 * Returns: uint16
 *******************************************************************************/
uint16 Ultrasonic_readDistance(void);

#endif /* HCSR04_ULTRASONIC_SENSOR_H_ */
