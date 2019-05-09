/*
  Flipdot_pins.h - Pin definitions
  The cake is a lie.
*/

#ifndef FLIPDOT_PINS_H_
#define FLIPDOT_PINS_H_

//Pin definitions
//		DEF NAME	I/O pins	NAME				CONNECTOR NAME

#define f_DDR_A		DDRB		//A					A
#define f_PORT_A	PORTB
#define f_BIT_A		0

#define f_DDR_B		DDRB		//B					B
#define f_PORT_B	PORTB
#define f_BIT_B		1

#define f_DDR_C		DDRB		//C					C
#define f_PORT_C	PORTB
#define f_BIT_C		2

#define f_DDR_RA	DDRD		//Row A				RA
#define f_PORT_RA	PORTD
#define f_BIT_RA	0

#define f_DDR_RB	DDRD		//Row B				RB
#define f_PORT_RB	PORTD
#define f_BIT_RB	1

#define f_DDR_RC	DDRD		//Row C				RC
#define f_PORT_RC	PORTD
#define f_BIT_RC	2

#define f_DDR_RE	DDRD		//Row Enable		RE
#define f_PORT_RE	PORTD
#define f_BIT_RE	3

#define f_DDR_EA	DDRD		//Subsegment A		EA
#define f_PORT_EA	PORTD
#define f_BIT_EA	5

#define f_DDR_EB	DDRD		//Subsegment B		EB
#define f_PORT_EB	PORTD
#define f_BIT_EB	6

#define f_DDR_EC	DDRD		//Subsegment C		EC
#define f_PORT_EC	PORTD
#define f_BIT_EC	7

#define f_DDR_SA	DDRC		//Segment A			Internal (SA)
#define f_PORT_SA	PORTC
#define f_BIT_SA	0

#define f_DDR_SB	DDRC		//Segment B			Internal (SB)
#define f_PORT_SB	PORTC
#define f_BIT_SB	1

#define f_DDR_SC	DDRC		//Segment C			Internal (SC)
#define f_PORT_SC	PORTC
#define f_BIT_SC	2

#endif
