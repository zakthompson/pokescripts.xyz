#include "../Joystick.h"
#include <avr/pgmspace.h>

static const Command m_command[] PROGMEM = {
    //----------Setup [0,2]----------
    // Press A once to connect
    {NOTHING, 30},
    {A, 1},
    {NOTHING, 1},

    //----------Spin [3,6]----------
    {UP_RIGHT, 1},
    {DOWN_RIGHT, 1},
    {DOWN_LEFT, 1},
    {UP_LEFT, 1},

    //----------Go back to corner [7,10]----------
    {LEFT, 10},
    {DOWN, 10},
    {PLUS, 1},
    {NOTHING, 20},

    //----------Go to nursery guy [11,35]----------
    {RIGHT, 23},
    {NOTHING, 2},
    {UP, 7},

    {A, 60},            // Ah, it's you!
    {NOTHING, 1},
    {A, 60},            // Your Pokemon was holding an Egg!
    {NOTHING, 1},
    {A, 60},            // We don't know how it got there, but your Pokemon had it.
    {NOTHING, 1},
    {A, 40},            // You do want it, don't you?
    {NOTHING, 1},
    {A, 20},            // Show Yes/No
    {NOTHING, 1},
    {A, 150},           // Click yes & You received an egg from the Nursery Man
    {NOTHING, 1},
    {B, 1},             // ???
    {NOTHING, 1},
    {B, 60},            // The Egg has been sent to a Box!
    {NOTHING, 1},
    {B, 40},            // You take good care of it.
    {NOTHING, 1},
    {B, 1},             // ??
    {NOTHING, 1},
    {B, 1},             // Close dialog
    {NOTHING, 1},

    //----------Go back to corner [36,39]----------
    {LEFT, 30},
    {DOWN, 10},
    {PLUS, 1},
    {NOTHING, 20},
};