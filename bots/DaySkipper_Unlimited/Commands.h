#include "../Joystick.h"
#include <avr/pgmspace.h>

static const Command m_command[] PROGMEM = {
	//----------Setup [0,8]----------
	// Press A once to connect
	{NOTHING, 30},
	{A, 1},
	{NOTHING, 1},

	// Make sure cursor is on OK
	{A, 1},
	{NOTHING, 1},
	{RIGHT, 40},
	{NOTHING, 1},

	// Exit
	{A, 1},
	{NOTHING, 4},

	//----------Skip day JP [9,17]----------
	// Enter
	{A, 1},
	{NOTHING, 4},

	// Move to day
	{LEFT, 1},
	{L, 1},
	{LEFT, 1},

	// Increment day
	{UP, 1},

	// Move to OK
	{RIGHT, 1},

	// Exit
	{R, 1},
	{NOTHING, 4},

	//----------Skip day EU [18,30]----------
	// Enter
	{A, 1},
	{NOTHING, 4},

	// Move to day
	{LEFT, 1},
	{L, 1},
	{LEFT, 1},
	{L, 1},
	{LEFT, 1},

	// Increment day
	{UP, 1},

	// Move to OK
	{RIGHT, 1},
	{R, 1},
	{RIGHT, 1},

	// Exit
	{A, 1},
	{NOTHING, 4},

	//----------Skip day US [31,43]----------
	// Enter
	{A, 1},
	{NOTHING, 4},

	// Move to day
	{LEFT, 1},
	{L, 1},
	{LEFT, 1},
	{L, 1},
	{LEFT, 1},

	// Increment day
	{UP, 1},

	// Move to OK
	{RIGHT, 1},
	{R, 1},
	{RIGHT, 1},

	// Exit
	{A, 1},
	{NOTHING, 4},

	//----------Back to game [44,47]----------
	{HOME, 1},
	{NOTHING, 30},
	{HOME, 1},
	{NOTHING, 30}
};
