/*
 * Copyright (C) eSrijan Innovations Private Limited
 * 
 * Author: Anil Kumar Pugalia <anil_pugalia@eSrijan.com>
 *
 * Licensed under: JSL (See LICENSE file for details)
 *
 * ATmega16/32
 *
 * Character LCD Demo using serial interaction. CLCD assumed to be connected as
 * specified in the comments of clcd.c.
 *
 * For trying this example on DDK's, make sure of the following:
 * 	DDK v1.1: RX jumper should be on the left-most pin pair.
 * 	DDK v2.1: Both RX-TX jumpers should be on the right-most pin pairs.
 */

#include <avr/io.h>

#include "clcd.h"
#include "serial.h"

int main(void)
{
	char c;
	uint8_t pos = 0;

	clcd_init();
	/*
	 * Optionally, now set up our application-specific display settings,
	 * overriding whatever we did in clcd_init()
	 */
	//clcd_cmd_wr(0x0F); // All On: Cursor, Display, Blink. (nasty!)
	clcd_print_string("Welcome Duniya");
	clcd_move_to(0);
	usart_init(9600);
	usart_byte_rx(); // Waiting for a character, typically an <Enter>
	usart_tx("Welcome to eSrijan's RS232 -> CLCD\r\n");

	while (1)
	{
		usart_tx("\r\neSrijan> ");
		c = usart_byte_rx();
		if (c == 27)
		{
			clcd_cls();
			pos = 0;
			continue;
		}
		if (c == '\b')
		{
			if ((pos != 0) && (pos != 16))
			{
				pos--;
				clcd_move_to(pos);
				clcd_data_wr(' ');
				clcd_move_to(pos);
			}
			continue;
		}
		if (pos == 16)
		{
			clcd_move_to(pos);
		}
		else if (pos == 32)
		{
			pos = 0;
			clcd_move_to(pos);
		}
		clcd_data_wr(c);
		pos++;
	}

	return 0;
}
