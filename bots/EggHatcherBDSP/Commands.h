#include "../Joystick.h"
#include <avr/pgmspace.h>

static const Command m_command[] PROGMEM = {
    //----------Setup [0,2]----------
    // Press A once to connect
    {NOTHING, 30},
    {B, 1},
    {NOTHING, 1},

    //----------Pick up eggs [3,30]----------
    // Go to correct column
    {RIGHT, 1},
    {NOTHING, 1},
    {RIGHT, 1},
    {NOTHING, 1},
    {RIGHT, 1},
    {NOTHING, 1},
    {RIGHT, 1},
    {NOTHING, 1},
    {RIGHT, 1},
    {NOTHING, 1},

    // Select Eggs
    {A, 10},
    {DOWN, 1},
    {NOTHING, 1},
    {DOWN, 1},
    {NOTHING, 1},
    {DOWN, 1},
    {NOTHING, 1},
    {DOWN, 1},
    {NOTHING, 10},
    {A, 10},

    // Put in party, exit
    {LEFT, 50},
    {DOWN, 2},
    {A, 30},
    {B, 1},
    {NOTHING, 68},
    {B, 1},
    {NOTHING, 54},
    {B, 41},

    //----------Put hatched egg to box [31,54]----------
	{X, 22},	
	{A, 64},
	{R, 1},			// Goto Box
	{NOTHING, 70},
	{Y, 1},
	{NOTHING, 1},
	{Y, 3},			// Multiselect mode
	{LEFT, 10},
	{DOWN, 3},
	{A, 3},			// Pick up hatched mons
	{DOWN, 50},
	{A, 3},
	{DOWN, 45},		// Put them to the current box
	{RIGHT, 2},
	{A, 1},         // Open box list
	{NOTHING, 20},
	{A, 10},        // Put in box
	{B, 15},        // Close box list
	{DOWN, 1},		// Back to top left corner
	{NOTHING, 15},
	{DOWN, 1},	
	{NOTHING, 15},
	
	{R, 1},			// Next Box
	{NOTHING, 20},

    //----------Go back to corner [55,56]----------
    {LEFT, 40},
    {DOWN, 10},

    //----------Cycle Loop [57,60]----------
    {UP_RIGHT, 1},
    {DOWN_RIGHT, 1},
    {DOWN_LEFT, 1},
    {UP_LEFT, 1},

    //----------Offset drift [61,62]----------
    {LEFT, 1},      // For some reason you may or may not slowly drift right and up
    {DOWN, 1},

	//----------Hatching Eggs x5 [63,68]----------
	{A, 1},
	{NOTHING, 1},
	{A, 800},		// Wait long in case it was a shiny
	{NOTHING, 1},
	{A, 130},
	{NOTHING, 1},
	
	//----------Finish [69,71]----------
	{NOTHING, 1},
	{HOME, 1},
	{NOTHING, 1},

	//----------Reset step counter [72,76]----------
    {R, 1},
    {NOTHING, 5},
    {A, 1},
    {R, 1},
    {NOTHING, 5},
};