/*
Pokemon Sword & Shield Fast Egg Hatching
Logic by kirbunkle aka Adam Hanny
Based on the LUFA library's Low-Level Joystick Demo
	(C) Dean Camera
Based on the HORI's Pokken Tournament Pro Pad design
	(C) HORI
This project implements a modified version of HORI's Pokken Tournament Pro Pad
USB descriptors to allow for the creation of custom controllers for the
Nintendo Switch. This also works to a limited degree on the PS3.
Since System Update v3.0.0, the Nintendo Switch recognizes the Pokken
Tournament Pro Pad as a Pro Controller. Physical design limitations prevent
the Pokken Controller from functioning at the same level as the Pro
Controller. However, by default most of the descriptors are there, with the
exception of Home and Capture. Descriptor modification allows us to unlock
these buttons for our use.
*/

#include <stdlib.h>
#include "Joystick.h"

/*------------------------------------------*/
// INSTRUCTIONS
// -> Your player must be on their bicycle in Bridge Field, no menus or dialogues open
// -> You must have ONLY 1 pokemon in your party
// -> The pokemon in your party needs to have Flame Body, Magma Armor, or Steam Engine
// -> You must be disconnected from the internet
// -> Your cursor must be over "Town Map" in the main menu (game remembers its position)
// -> Your main menu must be the default without menu items moved around!
// -> If they are moved, "Town Map" needs to be 1 down and 1 left from "Pokemon" in the main menu
// -> You must have a series of EMPTY boxes that you want to fill, and you must have selected the
//    first empty box in the series (game remembers which box you had open last)
// -> You have to start this program at the Change Grip/Order menu

/*------------------------------------------*/
// NOTES
// -> This program does not guarantee picking up the maximum number of eggs per cycle due to the
//    RNG for collecting eggs. If you have the oval charm, and the pokemon are same species and different
//    trainers, there is an 88% chance per pick-up that an egg will be available. This means even given
//    the best setup, you will likely only hatch ~9 eggs per two cycles, and not 10. The bot cannot
//    know if we pick up an egg or not, so we assume that we always get an egg. You will most definitely
//    have some empty spaces in your boxes after running this for a while, but it can't be helped.
// -> For reasons mentioned above, it is highly recommended that you have the oval charm. 
// -> Adjust the value for NUMBER_OF_BOXES_TO_FILL below to the number of sequential empty boxes you
//    have available.
// -> The table below shows the number of steps to hatch an egg, and then the recommended settings based on
//    that information. If you find eggs in your boxes, or the bot gets desynced, you may want to increase
//    the HATCHING_TIME_SEC value below.

/*------------------------------------------*/
// RECOMMENDED SETTINGS
// -> You will want to find the number of steps it takes for your pokemon to hatch, that information
//    can be found here: https://bulbapedia.bulbagarden.net/wiki/List_of_Pok%C3%A9mon_by_base_Egg_cycles
// -> 5120 steps - HATCHING_TIME_SEC = 145, MAX_NUM_OF_EGGS = 5 (time to fill a box ~29 mins)

#define HATCHING_TIME_SEC 145      // seconds for hatching
#define MAX_NUM_OF_EGGS 5          // number of eggs to hold before hatching
#define NUMBER_OF_BOXES_TO_FILL 10 // how many empty boxes are available to be filled

/*------------------------------------------*/

static const Command commands[] = {
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


// Main entry point.
int main(void) {
	//srand(m_seed);
	// We'll start by performing hardware and peripheral setup.
	SetupHardware();
	// We'll then enable global interrupts for our use.
	GlobalInterruptEnable();
	// Once that's done, we'll enter an infinite loop.
	for (;;)
	{
		// We need to run our task to process and deliver data for our IN and OUT endpoints.
		HID_Task();
		// We also need to run the main USB management task.
		USB_USBTask();
	}
}

// Configures hardware and peripherals, such as the USB peripherals.
void SetupHardware(void) {
	// We need to disable watchdog if enabled by bootloader/fuses.
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	// We need to disable clock division before initializing the USB hardware.
	//clock_prescale_set(clock_div_1);
	// We can then initialize our hardware and peripherals, including the USB stack.

	#ifdef ALERT_WHEN_DONE
	// Both PORTD and PORTB will be used for the optional LED flashing and buzzer.
	#warning LED and Buzzer functionality enabled. All pins on both PORTB and \
PORTD will toggle when printing is done.
	DDRD  = 0xFF; //Teensy uses PORTD
	PORTD =  0x0;
                  //We'll just flash all pins on both ports since the UNO R3
	DDRB  = 0xFF; //uses PORTB. Micro can use either or, but both give us 2 LEDs
	PORTB =  0x0; //The ATmega328P on the UNO will be resetting, so unplug it?
	#endif
	// The USB stack should be initialized last.
	USB_Init();
}

// Fired to indicate that the device is enumerating.
void EVENT_USB_Device_Connect(void) {
	// We can indicate that we're enumerating here (via status LEDs, sound, etc.).
}

// Fired to indicate that the device is no longer connected to a host.
void EVENT_USB_Device_Disconnect(void) {
	// We can indicate that our device is not ready (via status LEDs, sound, etc.).
}

// Fired when the host set the current configuration of the USB device after enumeration.
void EVENT_USB_Device_ConfigurationChanged(void) {
	bool ConfigSuccess = true;

	// We setup the HID report endpoints.
	ConfigSuccess &= Endpoint_ConfigureEndpoint(JOYSTICK_OUT_EPADDR, EP_TYPE_INTERRUPT, JOYSTICK_EPSIZE, 1);
	ConfigSuccess &= Endpoint_ConfigureEndpoint(JOYSTICK_IN_EPADDR, EP_TYPE_INTERRUPT, JOYSTICK_EPSIZE, 1);

	// We can read ConfigSuccess to indicate a success or failure at this point.
}

// Process control requests sent to the device from the USB host.
void EVENT_USB_Device_ControlRequest(void) {
	// We can handle two control requests: a GetReport and a SetReport.

	// Not used here, it looks like we don't receive control request from the Switch.
}

// Process and deliver data from IN and OUT endpoints.
void HID_Task(void) {
	// If the device isn't connected and properly configured, we can't do anything here.
	if (USB_DeviceState != DEVICE_STATE_Configured)
		return;

	// We'll start with the OUT endpoint.
	Endpoint_SelectEndpoint(JOYSTICK_OUT_EPADDR);
	// We'll check to see if we received something on the OUT endpoint.
	if (Endpoint_IsOUTReceived())
	{
		// If we did, and the packet has data, we'll react to it.
		if (Endpoint_IsReadWriteAllowed())
		{
			// We'll create a place to store our data received from the host.
			USB_JoystickReport_Output_t JoystickOutputData;
			// We'll then take in that data, setting it up in our storage.
			while(Endpoint_Read_Stream_LE(&JoystickOutputData, sizeof(JoystickOutputData), NULL) != ENDPOINT_RWSTREAM_NoError);
			// At this point, we can react to this data.

			// However, since we're not doing anything with this data, we abandon it.
		}
		// Regardless of whether we reacted to the data, we acknowledge an OUT packet on this endpoint.
		Endpoint_ClearOUT();
	}

	// We'll then move on to the IN endpoint.
	Endpoint_SelectEndpoint(JOYSTICK_IN_EPADDR);
	// We first check to see if the host is ready to accept data.
	if (Endpoint_IsINReady())
	{
		// We'll create an empty report.
		USB_JoystickReport_Input_t JoystickInputData;
		// We'll then populate this report with what we want to send to the host.
		GetNextReport(&JoystickInputData);
		// Once populated, we can output this data to the host. We do this by first writing the data to the control stream.
		while(Endpoint_Write_Stream_LE(&JoystickInputData, sizeof(JoystickInputData), NULL) != ENDPOINT_RWSTREAM_NoError);
		// We then send an IN packet on this endpoint.
		Endpoint_ClearIN();
	}
}

#define ECHOES 2
uint8_t echoes = 0;
USB_JoystickReport_Input_t last_report;

int durationCount = 0;

const int8_t LAST_COMMAND = (sizeof(commands) / sizeof(commands[0])) - 1; // used for debugging

int8_t m_commandIndex = 0;    // current executing command
int8_t m_endIndex = 29;       // last command to execute in sequence, then we check for new command
int8_t m_eggCount = 0;        // how many eggs we are holding right now
int16_t m_spinCount = 0;      // how many times we have spun this iteration
int16_t m_spinMax = 0;        // how many times we need to spin to move on
int8_t m_phase = 0;           // 0 = collecting, 1 = hatching
int8_t m_columnPosition = 0;  // where the cursor is in the boxes menu
int8_t m_nextColumn = 1;      // where we want the cursor to be to drop the pokemon
int8_t m_boxesFilled = 0;     // number of boxes we filled up

// Prepare the next report for the host.
void GetNextReport(USB_JoystickReport_Input_t* const ReportData) {

	// Prepare an empty report
	memset(ReportData, 0, sizeof(USB_JoystickReport_Input_t));
	ReportData->LX = STICK_CENTER;
	ReportData->LY = STICK_CENTER;
	ReportData->RX = STICK_CENTER;
	ReportData->RY = STICK_CENTER;
	ReportData->HAT = HAT_CENTER;

	// Repeat ECHOES times the last report
	if (echoes > 0)
	{
		memcpy(ReportData, &last_report, sizeof(USB_JoystickReport_Input_t));
		echoes--;
		return;
	}
	
	// quit executing if we are at the last command
	if ((m_commandIndex == LAST_COMMAND) && (commands[m_commandIndex].button == NOTHING))
	{
		return;
	}
	
	// quit executing if we filled all the boxes
	if (m_boxesFilled >= NUMBER_OF_BOXES_TO_FILL) return;

	// Get the next command sequence (new start and end)
	if (m_commandIndex == -1)
	{		
		if (m_endIndex == 29) // we just picked up an egg (hopefully)
		{
		    m_eggCount++;

			if (m_eggCount < MAX_NUM_OF_EGGS)
			{
				m_commandIndex = 30; // spin 
				m_endIndex = 31;
				m_spinCount = 0;
				m_spinMax = 14; // 2 "spins" per second (7 seconds should be enough for next egg)
			}
			else 
			{
				m_phase = 1; // set to hatching phase
				m_commandIndex = 30; // spin
				m_endIndex = 31;
				m_spinCount = 0;
				m_spinMax = HATCHING_TIME_SEC * 2; // 2 "spins" per second
			}
		}
		else if (m_endIndex == 31) // We are spinning
		{
			m_spinCount++;
			if (m_spinCount < m_spinMax)
			{
				m_commandIndex = 30; // keep spinning
			}
			else
			{
				if (m_phase == 0) // we are still collecting
				{
					m_commandIndex = 6; // go back to get an egg
					m_endIndex = 29;
				}
				else
				{
					m_commandIndex = 32; // put mon in boxes
					m_endIndex = 66;
					m_phase = 0; // set to egg collecting phase
				}
			}
		}
		else if (m_endIndex == 66) // We opened the pokemon menu, selected the pokemon, and moved right
		{
			m_columnPosition++;
			if (m_columnPosition < m_nextColumn)
			{
				m_commandIndex = 65; // we need to keep moving right
			}
			else
			{
				m_commandIndex = 67; // we are at an open column, put them in
				m_endIndex = 70;
			}
		}
		else if (m_endIndex == 70) // We just put the pokemon in the box
		{
			if (m_nextColumn < 6)
			{
				m_commandIndex = 73; // just quit the menu
				m_endIndex = 80;
				m_nextColumn++;
			}
			else
			{
				m_commandIndex = 71; // advance to the next box, then quit the menu
				m_endIndex = 80;
				m_nextColumn = 1;
				m_boxesFilled++;
			}
		}
		else if (m_endIndex == 80) // We finished putting away the hatched mon and are in the menu
		{
			m_eggCount = 0;
			m_columnPosition = 0;
			m_commandIndex = 8; // start over!
			m_endIndex = 29;
		}			
	}

	Buttons_t button = commands[m_commandIndex].button;
	if (button == UP)
	{
		ReportData->LY = STICK_MIN;
	}
	else if (button == LEFT)
	{
		ReportData->LX = STICK_MIN;
	}
	else if (button == DOWN)
	{
		ReportData->LY = STICK_MAX;
	}
	else if (button == RIGHT)
	{
		ReportData->LX = STICK_MAX;
	}
	else if (button == UP_RIGHT)
	{
		ReportData->LY = STICK_MIN;
		ReportData->LX = STICK_MAX;
	}
	else if (button == UP_LEFT)
	{
		ReportData->LY = STICK_MIN;
		ReportData->RX = STICK_MIN;
	}
	else if (button == ZL)
	{
		ReportData->Button |= SWITCH_A;
		ReportData->LY = STICK_MIN;
		ReportData->RX = STICK_MIN;
	}
	else if (button == X)
	{
		ReportData->Button |= SWITCH_X;
	}
	else if (button == Y)
	{
		ReportData->Button |= SWITCH_Y;
	}
	else if (button == A)
	{
		ReportData->Button |= SWITCH_A;
	}
	else if (button == B)
	{
		ReportData->Button |= SWITCH_B;
	}
    else if (button == R)
	{
		ReportData->Button |= SWITCH_R;
	}
	else if (button == PLUS)
	{
		ReportData->Button |= SWITCH_PLUS;
	}
	else if (button == TRIGGERS)
	{
		ReportData->Button |= SWITCH_L | SWITCH_R;
	}
	else if (button == HOME)
	{
		ReportData->Button |= SWITCH_HOME;
	}

	durationCount++;

	if (durationCount > commands[m_commandIndex].duration)
	{
		m_commandIndex++;
		durationCount = 0;

		// We reached the end of a command sequence
		if (m_commandIndex > m_endIndex)
		{
			m_commandIndex = -1;
		}
	}

	// Prepare to echo this report
	memcpy(&last_report, ReportData, sizeof(USB_JoystickReport_Input_t));
	echoes = ECHOES;
}
