#include "../Joystick.h"
#include <avr/pgmspace.h>

static const Command m_command[] PROGMEM = {
	//----------Setup [0,8]----------
	// Press A once to connect
	{NOTHING, 80},
	{A, 3},
	{NOTHING, 14},

	// Make sure cursor is on OK
	{A, 5},
	{NOTHING, 14},
	{RIGHT, 120},
	{NOTHING, 3},

	// Exit
	{A, 5},
	{NOTHING, 14},

	//----------Skip day JP [9,17]----------
	// Enter
	{A, 5},
	{NOTHING, 14},

	// Move to day
	{LEFT, 4},
	{L, 1},
	{LEFT, 4},

	// Increment day
	{UP, 4},

	// Move to OK
	{RIGHT, 4},

	// Exit
	{R, 5},
	{NOTHING, 14},

	//----------Skip day EU/US [18,30]----------
	// Enter
	{A, 5},
	{NOTHING, 14},

	// Move to day
	{LEFT, 4},
	{L, 4},
	{LEFT, 4},
	{L, 4},
	{LEFT, 4},

	// Increment day
	{UP, 4},

	// Move to OK
	{RIGHT, 4},
	{R, 4},
	{RIGHT, 4},

	// Exit
	{A, 4},
	{NOTHING, 14},

	//----------Back to game [31,34]----------
  {NOTHING, 30},
	{HOME, 4},
	{NOTHING, 150},
	{HOME, 4},
};
