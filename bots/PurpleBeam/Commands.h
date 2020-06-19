#include "../Joystick.h"
#include <avr/pgmspace.h>

static const Command m_command[] PROGMEM = {
	//----------Setup [0,2]----------
	// Press B once to connect
	{NOTHING, 30},
	{B, 1},
	{NOTHING, 1},
	
	//----------Ring bell like crazy then throw in wishing Piece [3,30]----------
	{LCLICK, 1},
	{NOTHING, 10},
	{LCLICK, 1},
	{NOTHING, 10},
	{LCLICK, 1},
	{NOTHING, 10},
	{LCLICK, 1},
	{NOTHING, 10},
	{LCLICK, 1},
	{NOTHING, 10},
	{LCLICK, 1},
	{NOTHING, 10},
	{LCLICK, 1},
	{NOTHING, 10},
	{LCLICK, 1},
	{NOTHING, 10},
	{LCLICK, 1},
	{NOTHING, 10},
	{LCLICK, 1},
	{NOTHING, 10},
	{A, 100},		// Talk
	{NOTHING, 1},
	{A, 70},		// There doesn't seem to be anything in the den... Want to throw in a Wishing Piece?
	{NOTHING, 1},
	{A, 35},		// Would you like to save your adventure so far?
	{NOTHING, 1},
	{HOME, 1},
	{NOTHING, 300},
	
	//----------SR [31,41]----------
	{X, 1},			// Close game
	{NOTHING, 8},
	{A, 1},			// Comfirm close game
	{NOTHING, 120},
	{A, 1},			// Choose game
	{NOTHING, 50},
	{A, 1},			// Pick User
	{NOTHING, 800},
	{NOTHING, 280}, // Extra wait time if m_titleScreenBuffer is true
	{A, 1},			// Enter game
	{NOTHING, 460},
};
