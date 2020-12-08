#include "../Joystick.h"
#include <avr/pgmspace.h>

static const Command m_command[] PROGMEM = {
	//----------Setup [0,2]----------
	// Press A once to connect
	{NOTHING, 30},
	{A, 1},
	{NOTHING, 1},

	//----------Delete friend [3,14]----------
	{A, 1},
	{NOTHING, 30},
	{DOWN, 1},
	{NOTHING, 1},
	{A, 1},
	{NOTHING, 8},
	{A, 1},
	{NOTHING, 30},
	{A, 1},
	{NOTHING, 300},
	{A, 1},
	{NOTHING, 40},

	//----------Navigate to Add friend [15,24]----------
	
	{B, 1},
	{NOTHING, 1},
	{DOWN, 1},
	{NOTHING, 1},
	{DOWN, 1},
	{NOTHING, 1},
	{DOWN, 1},
	{NOTHING, 1},
	{DOWN, 1},       //Extra button added in ver 11.0
	{NOTHING, 1},    //Extra button added in ver 11.0

	//----------A Spam [25,26]----------
	{A, 1},
	{NOTHING, 4},
};
