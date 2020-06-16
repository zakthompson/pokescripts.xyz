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

	//----------Back to game [9,12]----------
	{NOTHING, 30},
	{HOME, 4},
	{NOTHING, 150},
	{HOME, 4},

	//----------Skip day JP [13,21]----------
	{A, 5},
	{NOTHING, 14},

	// <<<^>>>
	{LEFT, 4},
	{RLEFT, 4},
	{LEFT, 4},
	{UP_A, 4},
	{RRIGHT, 4},

	{RIGHT_A, 5},
	{NOTHING, 14},

	//----------Skip month JP [22,33]----------
	{A, 5},
	{NOTHING, 14},

	// <<<^<^>>>>
	{LEFT, 4},
	{RLEFT, 4},
	{LEFT, 4},
	{UP, 4},
	{RLEFT, 4},
	{UP_A, 4},
	{RIGHT, 4},
	{RRIGHT, 4},

	{RIGHT_A, 5},
	{NOTHING, 14},

	//----------Skip year JP [34,48]----------
	{A, 5},
	{NOTHING, 14},

	// <<<^<^<^>>>>>
	{LEFT, 4},
	{RLEFT, 4},
	{LEFT, 4},
	{UP, 4},
	{RLEFT, 4},
	{UP, 4},
	{LEFT, 4},
	{UP_A, 4},
	{RRIGHT, 4},
	{RIGHT, 4},
	{RRIGHT, 4},

	{RIGHT_A, 5},
	{NOTHING, 14},

	//----------Skip day EU/US [49,61]----------
	{A, 5},
	{NOTHING, 14},

	// <<<<<^>>>>>
	{LEFT, 4},
	{RLEFT, 4},
	{LEFT, 4},
	{RLEFT, 4},
	{LEFT, 4},
	{UP_A, 4},
	{RRIGHT, 4},
	{RIGHT, 4},
	{RRIGHT, 4},

	{RIGHT_A, 5},
	{NOTHING, 14},

	//----------Skip month EU [62,75]----------
	{A, 5},
	{NOTHING, 14},

	// <<<<<^>^>>>>
	{LEFT, 4},
	{RLEFT, 4},
	{LEFT, 4},
	{RLEFT, 4},
	{LEFT, 4},
	{UP_A, 4},
	{NOTHING, 2},
	{UP_A, 4},
	{RIGHT, 4},
	{RRIGHT, 4},

	{RIGHT_A, 5},
	{NOTHING, 14},

	//----------Skip year EU [76,90]----------
	{A, 5},
	{NOTHING, 14},

	// <<<<<^>^>^>>>
	{LEFT, 4},
	{RLEFT, 4},
	{LEFT, 4},
	{RLEFT, 4},
	{LEFT, 4},
	{UP_A, 4},
	{NOTHING, 2},
	{UP_A, 4},
	{NOTHING, 2},
	{UP_A, 4},
	{RRIGHT, 4},

	{RIGHT_A, 5},
	{NOTHING, 14},

	//----------Skip month US [91,106]----------
	{A, 5},
	{NOTHING, 14},

	// <<<<<^<^>>>>>>
	{LEFT, 4},
	{RLEFT, 4},
	{LEFT, 4},
	{RLEFT, 4},
	{LEFT, 4},
	{UP, 4},
	{RLEFT, 4},
	{UP_A, 4},
	{RIGHT, 4},
	{RRIGHT, 4},
	{RIGHT, 4},
	{RRIGHT, 4},

	{RIGHT_A, 5},
	{NOTHING, 14},

	//----------Skip year US [107,122]----------
	{A, 5},
	{NOTHING, 14},

	// <<<<<^<^>>^>>>>
	{LEFT, 4},
	{RLEFT, 4},
	{LEFT, 4},
	{RLEFT, 4},
	{LEFT, 4},
	{UP, 4},
	{RLEFT, 4},
	{UP_A, 4},
	{RRIGHT, 4},
	{UP_A, 4},
	{RIGHT, 4},
	{RRIGHT, 4},

	{RIGHT_A, 5},
	{NOTHING, 14}
};
