#include "../Joystick.h"
#include <avr/pgmspace.h>

static const Command m_command[] PROGMEM = {
	//----------Setup [0, 2]----------
  // Press B once to connect
	{NOTHING, 30},
	{B, 1},
	{NOTHING, 1},

	// Open menu
	{X,            1}, // 3 - open menu
	{NOTHING,     20},

	// Fly to day care center in Bridge Field
	{A,            1}, // 5 - select town map
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
	{A,            1}, // 15 - talk to day-care lady
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
	{UP,          10}, // 25
	{UP_RIGHT,   110}, // 26 - move to spinning spot

	// spinner
	{ZL,           1}, // 27 - ZL repurposed to be UP_LEFT + A
	{UP_LEFT,     19}, // 28 - go to 27 until done spinning, then if we need more eggs, go to 3, if not, go to 29

	// Put hatched mons away
	{NOTHING,     20}, // 29
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
	{NOTHING,     10}, // 61

	// Position selected mons into box
	{RIGHT,        1}, // 62
	{NOTHING,     10}, // 63 - go to 62 if we need to keep going right, else go to 61

	// Drop em
	{UP,           1}, // 64 - position cursor
	{NOTHING,     10},
	{A,            1}, // drop selected mons into box
	{NOTHING,     40}, // 67 - if we are at the end of the box, go to 68, else go to 70

	// Position to next box if we need to
	{R,            1}, // 68
	{NOTHING,     60}, // 69

	{B,            1}, // 70 - exit box menu
	{NOTHING,    120},
	{B,            1}, // exit pokemon menu
	{NOTHING,    120},
	{DOWN,         1}, // position cursor
	{NOTHING,      1},
	{LEFT,         1}, // position cursor to town map
	{NOTHING,      1}, // 77 - go to 5

	// last instruction, basically stays here forever if we hit this
	{NOTHING,   5200}
};
