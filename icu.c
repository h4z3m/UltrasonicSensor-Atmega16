/******************************************************************************
 *
 * Module: ICU
 *
 * File Name: icu.c
 *
 * Description: Source file for ICU driver
 *
 * Date Created: 12/10/2021
 *
 * Author: Hazem Montasser
 *
 *******************************************************************************/

#include "icu.h"
#include "gpio.h"
#include <avr/io.h>
#include <avr/interrupt.h>
/*******************************************************************************
 *                           Global Variables (Private)                        *
 *******************************************************************************/
static volatile void (*g_ICU_callBack_Ptr)(void) = NULL_PTR;
/*******************************************************************************
 *                              ISR's Definitions                              *
 *******************************************************************************/
ISR(TIMER1_CAPT_vect) {
	if (g_ICU_callBack_Ptr != NULL_PTR) {
		(*g_ICU_callBack_Ptr)();
	}
}

/*******************************************************************************
 *                              Functions Definitions                          *
 *******************************************************************************/
void ICU_init(const ICU_ConfigType *Config_Ptr) {

	/* Must set to 1 if not using PWM mode */
	TCCR1A = (1 << FOC1A) | (1 << FOC1B);

	/* Insert Timer1 clock into first 3 bits*/
	TCCR1B = (Config_Ptr->clock) | (TCCR1B & 0xF8);

	/* Insert edge into 7th bit */
	TCCR1B |= (Config_Ptr->edge << ICES1) | (TCCR1B & 0xBF);

	/* Clear timer counter and ICU registers*/
	TCNT1 = 0;
	ICR1 = 0;

	/* Setup ICU pin as input*/
	GPIO_setupPinDirection(PORTD_ID, PIN6_ID, PIN_INPUT);
	//DDRD &= ~(1 << PD6);

	/* Enable ICU interrupt*/
	TIMSK |= (1 << TICIE1);

}
void ICU_setCallBack(void (*a_ptr)(void)) {
	g_ICU_callBack_Ptr = a_ptr;
}
void ICU_setEdgeDetectionType(const ICU_EdgeType a_edgeType) {
	/* Insert edge into 7th bit */
	TCCR1B = (a_edgeType << ICES1) | (TCCR1B & 0xBF);
}
uint16 ICU_getInputCaptureValue(void) {
	return ICR1;
}
void ICU_clearTimerValue(void) {
	TCNT1 = 0;
}
void ICU_DeInit(void) {
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;
	TIMSK &= ~(1 << TICIE1);
}
