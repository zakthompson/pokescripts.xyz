#include "../../Joystick.h"
#include <avr/pgmspace.h>

static const Command m_command[] PROGMEM = {
	//----------Setup [0,2]----------
	// Press A once to connect
	{NOTHING, 30},
	{B, 1},
	{NOTHING, 1},
	
	//----------Prepare to release [3,14]----------
	{A, 1},
	{NOTHING, 1},
	{UP, 1},
	{NOTHING, 1},
	{UP, 1},
	{NOTHING, 1},
	{A, 30},
	{NOTHING, 1},
	{DOWN, 1},
	{NOTHING, 1},
	{A, 1},
	{NOTHING, 25},

	//----------Releasing [15,20]-------------
	{RIGHT, 1}, // 15
	{A, 1},

	{DOWN, 1}, // 17
	{A, 1},

	{LEFT, 1}, // 19
	{A, 1},

	//-----------Release the mons [21,30]-------------
	{PLUS, 1},
	{NOTHING, 1},
	{A, 20},
	{NOTHING, 1},
	{UP, 1},
	{NOTHING, 1},	
	{A, 1},
	{NOTHING, 30},
	{A, 1},
	{NOTHING, 30},

	//------------Move to next box and start from top [31,50]-----------
	{R, 1},
	{NOTHING, 10},
	{LEFT, 1},
	{NOTHING, 1},
	{LEFT, 1},
	{NOTHING, 1},
	{LEFT, 1},
	{NOTHING, 1},
	{LEFT, 1},
	{NOTHING, 1},
	{LEFT, 1},
	{NOTHING, 1},
	{UP, 1},
	{NOTHING, 1},
	{UP, 1},
	{NOTHING, 1},
	{UP, 1},
	{NOTHING, 1},
	{UP, 1},
	{NOTHING, 1},

	//------------Save changes [51,58]-----------
	{PLUS, 1},
	{NOTHING, 1},
	{A, 20},
	{NOTHING, 1},
	{A, 1},
	{NOTHING, 300},
	{A, 1},
	{NOTHING, 1},
};