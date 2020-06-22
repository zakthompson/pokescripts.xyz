#include "../Joystick.h"
#include <avr/pgmspace.h>

static const Command m_command[] PROGMEM = {
	//----------Setup [0,2]----------
	// Press B once to connect
	{NOTHING, 30},
	{B, 1},
	{NOTHING, 1},

	//----------Sync and unsync time, goto change date [3,40]----------
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

	//----------Collect Berry [53,70]----------
	{A, 16},		// It's a Berry tree. Do you want to shake it?
	{NOTHING, 1},
	{A, 12},
	{NOTHING, 1},
	{A, 170},		// Yes
	{NOTHING, 1},
	{B, 30},		// X fell from the tree!
	{NOTHING, 1},
	{B, 65},		// There are X Berries on the ground. Quit
	{NOTHING, 1},
	{B, 16},		// You picked up the Betties that fell from the tree!
	{NOTHING, 1},
	{B, 16},
	{NOTHING, 1},
	{B, 16},
	{NOTHING, 1},
	{B, 16},
	{NOTHING, 14},

	//----------Save Game [71,76]----------
	{X, 1},
	{NOTHING, 20},
	{R, 1},
	{NOTHING, 50},
	{A, 1},
	{NOTHING, 140}
};
