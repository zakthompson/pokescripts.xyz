#include "../../Joystick.h"
#include <avr/pgmspace.h>

static const Command m_command[] PROGMEM = {
	//----------Setup [0,2]----------
	// Press L once to connect
	{NOTHING, 10},
	{L, 1},
	{NOTHING, 1},
	
	//----------Buy Pokeball [3,16]----------
	{A, 1},
	{NOTHING, 10},
	{RIGHT, 1},
	{NOTHING, 1},
	{DOWN, 1},
	{NOTHING, 1},
	{A, 26},
	{NOTHING, 1},
	{A, 20},
	{NOTHING, 1},
	{A, 20},
	{NOTHING, 1},
	{A, 1},
	{NOTHING, 10},

	//----------Go to sell [17,24]-------------
	{B, 1},
	{NOTHING, 1},
	{A, 40},
	{NOTHING, 1},
	{DOWN, 1},
	{NOTHING, 1},
	{A, 1},
	{NOTHING, 70},

	//----------Selling [25,36]-------------

	{A, 1}, // How many Poke Balls would you like to sell?
	{NOTHING, 10},
	{RIGHT, 1}, // 27
	{NOTHING, 1}, // 28
	{DOWN, 1},
	{NOTHING, 1},
	{A, 26}, // I can pay you XXX. Would that be OK?
	{NOTHING, 1},
	{A, 20}, // You turned over the Poke Balls and got XXX.
	{NOTHING, 1},
	{A, 1},
	{NOTHING, 1},
};