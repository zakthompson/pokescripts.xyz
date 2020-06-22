#include "../Joystick.h"
#include <avr/pgmspace.h>

static const Command m_command[] PROGMEM = {
	//----------Setup [0,2]----------
	// Press A once to connect
	{NOTHING, 30},
	{A, 1},
	{NOTHING, 1},

	// To System Settings [3,11]
	{HOME, 1},
	{NOTHING, 30},
	{DOWN, 1},
	{NOTHING, 1},
	{RIGHT, 1},
	{RRIGHT, 1},
	{RIGHT, 1},
	{RRIGHT, 1},
	{A, 40},

	// To Date and Time [12,32]
	{DOWN, 1},
	{RDOWN, 1},
	{DOWN, 1},
	{RDOWN, 1},
	{DOWN, 1},
	{RDOWN, 1},
	{DOWN, 1},
	{RDOWN, 1},
	{DOWN, 1},
	{RDOWN, 1},
	{DOWN, 1},
	{RDOWN, 1},
	{DOWN, 1},
	{RDOWN, 1},
	{A, 12},
	{DOWN, 1},
	{RDOWN, 1},
	{DOWN, 1},
	{RDOWN, 1},
	{A, 1},
	{NOTHING, 12},

	// Sync and unsync time [33,36]
	{A, 1},
	{NOTHING, 4},
	{A, 1},
	{NOTHING, 12},

	// To actually Date and Time [37,40]
	{DOWN, 1},
	{RDOWN, 1},
	{A, 1},
	{NOTHING, 7},

	//----------Plus 1 year [41,48]----------
	{RIGHT_A, 1},		// EU/US start
	{NOTHING, 1},
	{UP_A, 1},		// JP start
	{RRIGHT, 1},
  {RIGHT_A, 1},
  {RRIGHT, 1},
	{A, 1},
	{NOTHING, 4},

	//----------Back to game [49,52]----------
	{HOME, 1},
	{NOTHING, 30},
	{HOME, 1},
	{NOTHING, 30},

	//----------Collect Watts [53,60]----------
	{A, 12},
	{NOTHING, 1},
	{B, 6},
	{NOTHING, 1},
	{B, 30},
	{NOTHING, 1},
	{B, 1},
	{NOTHING, 50},

	//----------Save Game [61,66]----------
	{X, 1},
	{NOTHING, 20},
	{R, 1},
	{NOTHING, 50},
	{A, 1},
	{NOTHING, 140}
};
