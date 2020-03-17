/*
Pokemon Sword & Shield AUTO Raid Hosting - Proof-of-Concept

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
// INSTRUCTION
// -> THIS SCRIPT RELIES ON AIRPLANE MODE AND ONLY WORKS HANDHELD
// -> The benefit of the airplane mode method is you don't have to save-lock to a Pokemon
// -> You MUST stand in front of an active den (with watts already collected)
// -> Be careful if time is synced and past mid-night, you will start able to collect watts
// -> You MUST not have connected to the internet at the beginning
// -> You are adviced to have wired connection for stable and fast internet
// -> If you use WiFi you probably need to adjust your connection time below in code
// -> This program relies on clients to be ready before 2 minute mark, otherwise the raid fails
// -> Once the raid starts, it will turn on airplane mode to remove you from the raid
// -> You have to start this program at the Change Grip/Order menu
//
// KNOWN ISSUES
// -> Link codes currently do not work in this script (the indexes below need to be updated)

// -> Use optional link code or not? (true/false)
bool m_useLinkCode = false;

// -> Use random code (if m_useLinkCode = true)
// -> m_seed range is 0 to 255, same seed will always generate the same link code sequence
// -> As long as the board is not unplugged, the sequence will go random forever
// -> If the board is unplugged, the squence will start at the beginning again
bool m_useRandomCode = false;
uint8_t m_seed = 169;

// -> Set optional link code here (if m_useLinkCode = true, m_useRandomCode = false)
// -> e.g 4501: m_linkCode[] = {4,5,0,1};
// -> e.g 0389: m_linkCode[] = {0,3,8,9};
uint8_t m_linkCode[] = {1,6,4,9};
/*------------------------------------------*/

static const Command autoHost[] = {
	//----------Setup [0,5]----------
	// Connect controller in Change Grip/Order
	{NOTHING, 30},
	{TRIGGERS, 30},
	{A, 40},
	{B, 40},
	{HOME, 1},
	{NOTHING, 60},

	//----------Connect Internet [6,12]----------
	{Y, 50},
	{PLUS, 1000},		// Internet connection time (400 ~= 9 seconds wait)
	{B, 1},
	{NOTHING, 6},
	{B, 140},			// Allow time to load other players
	{A, 1},				// Interact with den
	{NOTHING, 200}, 	// Communicating... standing by

	//----------Confirm link code [13,15]----------
	{PLUS, 51},
	{A, 1},
	{NOTHING, 30},

	//----------Start raid [16,23]----------
	{A, 2600},			// (5200 ~= until 1 min, 2600 ~= until 2 min)
	{UP, 2},
	{A, 1},
	{NOTHING, 20},
	{A, 50},
	{NOTHING, 1},
	{A, 1},
	/* {NOTHING, 800},	// Wait until game starting showing abilities (if any has one) */
  {NOTHING, 500},

	//----------Finish/Prepare SR [24,34]----------
  /* {HOME, 1},                      */
  /* {NOTHING, 40},                  */
  /* {X, 9},			// Close game         */
  /* {A, 1},			// Comfirm close game */
  /* {NOTHING, 120},                 */
  /* {A, 1},			// Choose game        */
  /* {NOTHING, 50},                  */
  /* {A, 1},			// Pick User          */
  /* {NOTHING, 800},                 */
  /* {A, 1},			// Enter game         */
  /* {NOTHING, 460},                 */

  //----------Airplane On/Off [24, 33]----------
  // NOTE:  This breaks link codes
  {HOME, 40},
  {DOWN, 40},
  {A, 1},
  {NOTHING, 10},
  {A, 1},
  {NOTHING, 10},
  {B, 1},
  {NOTHING, 40},
  {A, 1},
  {NOTHING, 1200},

	//----------Set Link Code [33, 57]----------
	// Init
	{PLUS, 35},

	// Reset to 0
	{DOWN, 1},
	{NOTHING, 1},
	{DOWN, 1},
	{NOTHING, 1},
	{DOWN, 1},
	{NOTHING, 1},

	// Press A
	{A, 1},
	{NOTHING, 1},

	// 1,4,7,2,5,8 [42-49]
	{UP, 1},
	{NOTHING, 1},
	{UP, 1},
	{NOTHING, 1},
	{UP, 1},
	{NOTHING, 1},
	{LEFT, 1},
	{NOTHING, 1},

	// 3,6,9 [50-57]
	{UP, 1},
	{NOTHING, 1},
	{UP, 1},
	{NOTHING, 1},
	{UP, 1},
	{NOTHING, 1},
	{RIGHT, 1},
	{NOTHING, 1},
};


// Main entry point.
int main(void) {
	srand(m_seed);
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

// start and end index of "Setup"
int8_t commandIndex = 0;
int8_t m_endIndex = 5;
uint8_t m_sequence = 0;

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

	// Get the next command sequence (new start and end)
	if (commandIndex == -1)
	{
		m_sequence++;

		if (m_sequence == 1)
		{
			// Connect internet and enter raid
			commandIndex = 6;	// 6 = go online, 11 = local only
			m_endIndex = 12;
		}
		else if (m_sequence == 2)
		{
			if (!m_useLinkCode)
			{
				// Skip to start raid, invite, SR
				commandIndex = 16;
				m_endIndex = 33;

				m_sequence = 0;
			}
			else
			{
				// Prepare link code, goto 0
				commandIndex = 31;
				m_endIndex = 37;
			}
		}
		else if (m_sequence == 14)
		{
			// Finish setting link code, invite others, SR
			commandIndex = 13;
			m_endIndex = 34;

			m_sequence = 0;
		}
		else //if (m_sequence <= 13)
		{
			// Entering link code
			if (m_sequence % 3 == 0) // 3,6,9,12
			{
				uint8_t number = m_useRandomCode ? (rand() % 10) : m_linkCode[m_sequence / 3 - 1];

				if (number == 0)
				{
					return;

					// Just press A for 0
					commandIndex = 42;
					m_endIndex = 43;

					// Skip going down
					m_sequence += 2;
				}
				else if (number % 3 == 0) // 3,6,9
				{
					commandIndex = 52 + (number / 3 - 1) * 2;
					m_endIndex = 59;
				}
				else // 1,4,7,2,5,8
				{
					commandIndex = 44 + (number / 3) * 2;
					m_endIndex = (number % 3 == 1) ? 51 : 49;
				}
			}
			else if (m_sequence % 3 == 1) // 4,7,10,13
			{
				// Press A
				commandIndex = 42;
				m_endIndex = 43;
			}
			else // 5,8,11
			{
				// Reset to 0
				commandIndex = 36;
				m_endIndex = 41;
			}
		}
	}

	Buttons_t button = autoHost[commandIndex].button;
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

	if (durationCount > autoHost[commandIndex].duration)
	{
		commandIndex++;
		durationCount = 0;

		// We reached the end of a command sequence
		if (commandIndex > m_endIndex)
		{
			commandIndex = -1;
		}
	}

	// Prepare to echo this report
	memcpy(&last_report, ReportData, sizeof(USB_JoystickReport_Input_t));
	echoes = ECHOES;
}
