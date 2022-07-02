/*
 * main.c
 *
 *  Created on: Oct 12, 2021
 *      Author: h4z3m
 */
#include <avr/io.h>
#include <util/delay.h>
#include "hcsr04_ultrasonic_sensor.h"
#include "lcd.h"
/* Global value of measured distance by sensor */
uint16 APP_distance_measured = 0;
int main(void) {

	/* Initialize hardware modules */
	LCD_init();
	Ultrasonic_init();

	/* Slight delay until hardware is setup */
	_delay_ms(300);

	/* Display fixed message */
	LCD_displayString((const uint8*) "Distance=     cm");

	/* Enable global interrupts */
	SREG|=(1<<7);

	/*Super loop*/
	for (;;) {
		/* Read distance from sensor*/
		APP_distance_measured = Ultrasonic_readDistance();
		/* Display distance*/
		LCD_moveCursor(0, 10);
		if (APP_distance_measured < 10) {
			LCD_integerToString(APP_distance_measured);
			LCD_displayString((const uint8*) "  ");
		} else if (APP_distance_measured >= 10
				&& APP_distance_measured < 1000) {
			LCD_integerToString(APP_distance_measured);
			LCD_displayString((const uint8*) " ");
		}
		/* Slight delay to avoid simulation lag */
		_delay_ms(100);
	}
}
