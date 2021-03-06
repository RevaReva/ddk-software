/*
 * Copyright (C) eSrijan Innovations Private Limited
 * 
 * Author: Anil Kumar Pugalia <anil_pugalia@eSrijan.com>
 *
 * Licensed under: JSL (See LICENSE file for details)
 *
 * ATmega48/88/168, ATmega16/32
 * 
 * Reads switch input from PB2, and output the same to LED on PB7
 */

#include <avr/io.h>
#include <util/delay.h>

#include "ddk.h"

void init_io(void)
{
	// 1 = output, 0 = input
	BUTTON_INIT;
	DDRB |= 0b10000000;
}

int main(void)
{
	init_io();

	while (1)
	{
		if (BUTTON_PRESSED)
		{
			PORTB |= (1 << 7);
		}
		else
		{
			PORTB &= ~(1 << 7);
		}
	}

	return 0;
}
