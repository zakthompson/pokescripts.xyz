#include "../Joystick.h"
#include <avr/pgmspace.h>

static const Command m_command[] PROGMEM = {
	//----------Setup [0,5]----------
	// Connect controller in Change Grip/Order
	{NOTHING,     30},
	{TRIGGERS,    30},
	{A,           40},
	{B,           40},
	{HOME,         1},
	{NOTHING,    120},

	// Open menu
	{X,            1}, // 6 - open menu
	{NOTHING,     20},

	// Fly to day care center in Bridge Field
	{A,            1}, // 8 - select town map
	{NOTHING,    120},
	{A,            1}, // select day care center
	{NOTHING,     40},
	{A,            1}, // confirm
	{NOTHING,    120},

	// Ride to day care lady
	{LEFT,         1},
	{DOWN,        26},
	{RIGHT,        6},
	{NOTHING,     20},

	// Take egg OR leave if no egg is ready
	{A,            1}, // 18 - talk to day-care lady
	{NOTHING,     40},
	{A,            1}, // Yes to take egg (if no egg, advances dialogue)
	{NOTHING,    130}, // wait for jingle
	{B,            1}, // advance dialogue (or leave if no egg)
	{NOTHING,     60},
	{B,            1}, // advance dialogue
	{NOTHING,     60},
	{B,            1}, // close dialogue
	{NOTHING,     15},

	// go to spinning spot
	{UP,          10}, // 28
	{UP_RIGHT,   110}, // 29 - move to spinning spot

	// spinner
	{ZL,           1}, // 30 - ZL repurposed to be UP_LEFT + A
	{UP_LEFT,     19}, // 31 - go to 30 until done spinning, then if we need more eggs, go to 6, if not, go to 32

	// Put hatched mons away
	{NOTHING,     20}, // 32
	{B,            1},
	{NOTHING,     20},
	{X,            1}, // Open menu
	{NOTHING,     20},
	{RIGHT,        1}, // cursor right
	{NOTHING,      1},
	{UP,           1}, // cursor up, to pokemon menu
	{NOTHING,      1},
	{A,            1}, // select pokemon menu
	{NOTHING,    120},
	{R,            1}, // go to boxes
	{NOTHING,    120},
	{LEFT,         1},
	{NOTHING,      1},
	{DOWN,         1}, // cursor over first hatched mon
	{NOTHING,      1},
	{Y,            1}, // advance cursor type
	{NOTHING,      1},
	{Y,            1}, // advance cursor type to multi-select
	{NOTHING,      1},
	{A,            1}, // start multi-selecting
	{NOTHING,      1},
	{DOWN,         1},
	{NOTHING,      1},
	{DOWN,         1},
	{NOTHING,      1},
	{DOWN,         1},
	{NOTHING,      1},
	{DOWN,         1},
	{NOTHING,      1},
	{A,            1}, // select all hatched mons in party
	{NOTHING,     10}, // 64

	// Position selected mons into box
	{RIGHT,        1}, // 65
	{NOTHING,     10}, // 66 - go to 65 if we need to keep going right, else go to 67

	// Drop em
	{UP,           1}, // 67 - position cursor
	{NOTHING,     10},
	{A,            1}, // drop selected mons into box
	{NOTHING,     40}, // 70 - if we are at the end of the box, go to 71, else go to 73

	// Position to next box if we need to
	{R,            1}, // 71
	{NOTHING,     60}, // 72

	{B,            1}, // 73 - exit box menu
	{NOTHING,    120},
	{B,            1}, // exit pokemon menu
	{NOTHING,    120},
	{DOWN,         1}, // position cursor
	{NOTHING,      1},
	{LEFT,         1}, // position cursor to town map
	{NOTHING,      1}, // 80 - go to 8

	// last instruction, basically stays here forever if we hit this
	{NOTHING,   5200}
};
