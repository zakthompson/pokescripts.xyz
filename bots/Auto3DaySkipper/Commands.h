#include "../Joystick.h"
#include <avr/pgmspace.h>

static const Command m_command[] PROGMEM = {
	//----------Setup [0,2]----------
	// Press B once to connect
	{NOTHING, 30},
	{B, 1},
	{NOTHING, 1},

	//----------Sync and unsync time, goto change date [3,34]----------
	// To System Settings
	{HOME, 1},
	{NOTHING, 30},
	{DOWN, 1},
	{NOTHING, 1},
	{RIGHT, 1},
	{NOTHING, 1},
	{RIGHT, 1},
	{NOTHING, 1},
	{RIGHT, 1},
	{NOTHING, 1},
	{RIGHT, 1},
	{NOTHING, 1},
	{A, 1},
	{NOTHING, 1},

	// To Date and Time
	{DOWN, 80},
	{NOTHING, 1},
	{A, 1},
	{NOTHING, 1},
	{DOWN, 1},
	{NOTHING, 1},
	{DOWN, 1},
	{NOTHING, 1},
	{DOWN, 1},
	{NOTHING, 1},
	{DOWN, 1},
	{NOTHING, 1},
	{A, 1},
	{NOTHING, 8},

	// Sync and unsync time
	{A, 1},
	{NOTHING, 4},
	{A, 1},
	{NOTHING, 8},

	//----------Plus 1 year [35,48]----------
	// To actually Date and Time
	{DOWN, 1},
	{NOTHING, 1},
	{DOWN, 1},
	{NOTHING, 1},
	{A, 1},
	{NOTHING, 7},

	// Plus 1 year
	{RIGHT_A, 1},		// EU/US start
	{NOTHING, 1},
	{UP_A, 1},		// JP start
	{RRIGHT, 1},
  {RIGHT_A, 1},
  {RRIGHT, 1},
	{A, 1},
	{NOTHING, 4},

	//----------Back to game [49, 52]----------
	{HOME, 1},
	{NOTHING, 30},
	{HOME, 1},
	{NOTHING, 30},

	//----------Quit the raid [53,56]----------
	{B, 32},
	{NOTHING, 1},
	{A, 200},		// WAITING on local communication
	{NOTHING, 1},

	//----------Collect Watts [57,64]----------
	{A, 20},		// Talk
	{NOTHING, 1},
	{A, 6},			// There's energy pouring out from the den!
	{NOTHING, 1},
	{A, 30},		// You gained 2,000W!
	{NOTHING, 1},
	{A, 120},		// WAITING on local communication
	{NOTHING, 1},

	//----------Ring bike like mad, collect watts then delay [65,90]----------
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
	{A, 12},		// Talk
	{NOTHING, 1},
	{A, 6},			// There's energy pouring out from the den!
	{NOTHING, 1},
	{A, 30},		// You gained 2,000W! (Delay longer for player to check)
	{NOTHING, 300},

	//----------Finish/Prepare SR [91,103]----------
	{HOME, 1},
	{NOTHING, 40},
	{X, 1},			// Close game
	{NOTHING, 8},
	{A, 1},			// Comfirm close game
	{NOTHING, 120},
	{A, 1},			// Choose game
	{NOTHING, 50},
	{A, 1},			// Pick User
	{NOTHING, 720},
	{NOTHING, 280}, // Extra wait time if m_titleScreenBuffer is true
	{A, 1},			// Enter game
	{NOTHING, 460}
};
