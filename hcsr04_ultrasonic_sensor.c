/******************************************************************************
 *
 * Module: Ultrasonic Sensor (HCSR04)
 *
 * File Name: hcsr04_ultrasonic_sensor.h
 *
 * Description: Source file for the Ultrasonic sensor driver
 *
 * Author: Hazem Montasser
 *
 *******************************************************************************/

#include <avr/io.h>
#include <util/delay.h>
#include "hcsr04_ultrasonic_sensor.h"
/*******************************************************************************
 *                              Global Variables(Private)                      *
 *******************************************************************************/
static volatile uint16 T1 = 0, T2 = 0;

/*******************************************************************************
 *                              Functions Definitions                          *
 *******************************************************************************/

void Ultrasonic_init(void) {

	/* Setup sensor trigger pin as output from which we send a pulse */
	GPIO_setupPinDirection(HCSR04_TRIGGER_PORT, HCSR04_TRIGGER_PIN, PIN_OUTPUT);
	ICU_ConfigType Config = { ULTRASONIC_ICU_PRESCALER, RISING };

	/* Initialize ICU accordingly */
	ICU_init(&Config);

	/* Setup callback function to store ICR value */
	ICU_setCallBack(Ultrasonic_edgeProcessing);
}


void Ultrasonic_Trigger(void) {
	/* Send high pulse to trigger pin*/
	GPIO_writePin(HCSR04_TRIGGER_PORT, HCSR04_TRIGGER_PIN, LOGIC_HIGH);
	/* Wait at least 10us */
	_delay_us(HCSR04_PULSE_DURATION_US);
	/* Pull trigger pin to low to end pulse */
	GPIO_writePin(HCSR04_TRIGGER_PORT, HCSR04_TRIGGER_PIN, LOGIC_LOW);

}


void Ultrasonic_edgeProcessing(void) {
	static uint8 ticks = 0;
	if (ticks == 0) {
		/* On first rising edge, switch interrupt trigger to falling edge*/
		ICU_setEdgeDetectionType(FALLING);
		++ticks;
		/* Store ICU register captured on edge trigger */
		T1 = ICU_getInputCaptureValue();
	} else if (ticks == 1) {
		/* Store ICU register captured on edge trigger */
		T2 = ICU_getInputCaptureValue();
		/* On falling edge, switch interrupt trigger to rising edge*/
		ICU_setEdgeDetectionType(RISING);
		ticks = 0;
	}
}


uint16 Ultrasonic_readDistance(void) {
	volatile uint16 g_HCSR04_distance = 0;
	/* Send pulse to trigger an echo */
	Ultrasonic_Trigger();
	/* Calculate distance using the time difference obtained from ICU triggers */
	g_HCSR04_distance = ((uint32) ((T2 - T1)) * (double)(HCSR04_DISTANCE_CONSTANT));

	return g_HCSR04_distance;
}
