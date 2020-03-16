/*
Pokemon Sword & Shield AUTO Day Skipper - Proof-of-Concept

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

#include "Joystick.h"

/*------------------------------------------*/
// INSTRUCTION
// -> You MUST have y-comm glitch active and system time unsynced
// -> Set your date info here, date must be between 2000/1/1 to 2060/12/31 (22280 days advance)
// -> Use this website to check your end date: https://www.timeanddate.com/date/dateadd.html
// -> MAKE SURE the end date is within range, if your seed is over 22280 skips, enter the game
// to register the time skip, set a new start date, update this program and start again!
// -> It takes ~31 seconds per 30 days

int m_day = 3;
int m_month = 5;
int m_year = 2024;
int m_dayToSkip = 290;
/*------------------------------------------*/

static const Command daySkipper[] = {
	//----------Setup [0,8]----------
	// Press A once to connect
	{NOTHING, 30},
	{A, 1},
	{NOTHING, 1},
	
	// Make sure cursor is on OK
	{A, 1},
	{NOTHING, 1},
	{RIGHT, 40},
	{NOTHING, 1},
	
	// Exit
	{A, 1},
	{NOTHING, 4},
	
	//----------Skip day [9,26]----------
	// Enter
	{A, 1},
	{NOTHING, 5},
	
	// Move to day
	{LEFT, 1},
	{NOTHING, 1},
	{LEFT, 1},
	{NOTHING, 1},
	{LEFT, 1},
	{NOTHING, 1},
	
	// Increment day
	{UP, 1},
	{NOTHING, 1},
	
	// Move to OK
	{RIGHT, 1},
	{NOTHING, 1},
	{RIGHT, 1},
	{NOTHING, 1},
	{RIGHT, 1},
	{NOTHING, 1},

	// Exit
	{A, 1},
	{NOTHING, 4},
	
	//----------Skip month [27,50]----------
	// Enter
	{A, 1},
	{NOTHING, 5},
	
	// Move to day
	{LEFT, 1},
	{NOTHING, 1},
	{LEFT, 1},
	{NOTHING, 1},
	{LEFT, 1},
	{NOTHING, 1},
	
	// Set day back to "01"
	{UP, 1},
	{NOTHING, 1},
	
	// Move to month
	{LEFT, 1},
	{NOTHING, 1},

	// Increment month
	{UP, 1},
	{NOTHING, 1},
	
	// Move to OK
	{RIGHT, 1},
	{NOTHING, 1},
	{RIGHT, 1},
	{NOTHING, 1},
	{RIGHT, 1},
	{NOTHING, 1},
	{RIGHT, 1},
	{NOTHING, 1},

	// Exit
	{A, 1},
	{NOTHING, 4},
	
	//----------Skip year [51,80]----------
	// Enter
	{A, 1},
	{NOTHING, 5},
	
	// Move to day
	{LEFT, 1},
	{NOTHING, 1},
	{LEFT, 1},
	{NOTHING, 1},
	{LEFT, 1},
	{NOTHING, 1},
	
	// Set day back to "01"
	{UP, 1},
	{NOTHING, 1},
	
	// Move to month
	{LEFT, 1},
	{NOTHING, 1},

	// Set month back to "01"
	{UP, 1},
	{NOTHING, 1},
	
	// Move to year
	{LEFT, 1},
	{NOTHING, 1},

	// Increment year
	{UP, 1},
	{NOTHING, 1},
	
	// Move to OK
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

	// Exit
	{A, 1},
	{NOTHING, 4},
	
	//----------Back to game [81,84]----------
	{HOME, 1},
	{NOTHING, 30},
	{HOME, 1},
	{NOTHING, 20}
};


// Main entry point.
int main(void) {
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

typedef enum {
	PROCESS,
	DONE
} State_t;
State_t state = PROCESS;

#define ECHOES 2
int echoes = 0;
USB_JoystickReport_Input_t last_report;

int xpos = 0;
int ypos = 0;
int portsval = 0;

int durationCount = 0;

// start and end index of "Setup"
int commandIndex = 0;
int m_endIndex = 8;

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

	// States and moves management
	switch (state)
	{
		case PROCESS:
			// Get the next command sequence (new start and end)
			if (commandIndex == -1)
			{
				if (m_dayToSkip > 0)
				{
					// Day = 0, Month = 1, Year = 2
					int passDayMonthYear = 0;
					
					if (m_month == 2)
					{
						bool isLeapYear = (m_year % 4 == 0);
						if (isLeapYear && m_day == 29)
						{
							passDayMonthYear = 1;
						}
						else if (!isLeapYear && m_day == 28)
						{
							passDayMonthYear = 1;
						}
					}
					else if (m_month == 12 && m_day == 31)
					{
						passDayMonthYear = 2;
					}
					else if (m_month == 4 || m_month == 6 || m_month == 9 || m_month == 11)
					{
						if (m_day == 30)
						{
							passDayMonthYear = 1;
						}
					}
					else //if (m_month == 1 || m_month == 3 || m_month == 5 || m_month == 7 || m_month == 8 || m_month == 10)
					{
						if (m_day == 31)
						{
							passDayMonthYear = 1;
						}
					}
					
					if (passDayMonthYear == 0)
					{
						// Pass day
						m_day++;
						commandIndex = 9;
						m_endIndex = 26;
					}
					else if (passDayMonthYear == 1)
					{
						// Pass month
						m_day = 1;
						m_month++;
						commandIndex = 27;
						m_endIndex = 50;
					}
					else
					{
						// Pass year
						m_day = 1;
						m_month = 1;
						m_year++;
						commandIndex = 51;
						m_endIndex = 80;
					}
				}
				else if (m_dayToSkip == 0)
				{
					// Go back to game
					commandIndex = 81;
					m_endIndex = 84;
				}
				else
				{
					// Finish
					state = DONE;
					break;
				}
				
				m_dayToSkip--;
			}
		
			switch (daySkipper[commandIndex].button)
			{
				case UP:
					ReportData->LY = STICK_MIN;				
					break;

				case LEFT:
					ReportData->LX = STICK_MIN;				
					break;

				case DOWN:
					ReportData->LY = STICK_MAX;				
					break;

				case RIGHT:
					ReportData->LX = STICK_MAX;				
					break;

				/*case X:
					ReportData->Button |= SWITCH_X;
					break;

				case Y:
					ReportData->Button |= SWITCH_Y;
					break;*/

				case A:
					ReportData->Button |= SWITCH_A;
					break;

				/*case B:
					ReportData->Button |= SWITCH_B;
					break;

				case L:
					ReportData->Button |= SWITCH_L;
					break;

				case R:
					ReportData->Button |= SWITCH_R;
					break;

				case ZL:
					ReportData->Button |= SWITCH_ZL;
					break;

				case ZR:
					ReportData->Button |= SWITCH_ZR;
					break;

				case MINUS:
					ReportData->Button |= SWITCH_MINUS;
					break;

				case PLUS:
					ReportData->Button |= SWITCH_PLUS;
					break;

				case LCLICK:
					ReportData->Button |= SWITCH_LCLICK;
					break;

				case RCLICK:
					ReportData->Button |= SWITCH_RCLICK;
					break;

				case TRIGGERS:
					ReportData->Button |= SWITCH_L | SWITCH_R;
					break;*/

				case HOME:
					ReportData->Button |= SWITCH_HOME;
					break;

				/*case CAPTURE:
					ReportData->Button |= SWITCH_CAPTURE;
					break;*/

				default:
					// really nothing lol
					break;
			}

			durationCount++;

			if (durationCount > daySkipper[commandIndex].duration)
			{
				commandIndex++;
				durationCount = 0;		

				// We reached the end of a command sequence
				if (commandIndex > m_endIndex)
				{
					commandIndex = -1;
				}		
			}

			break;

		case DONE: return;
	}

	// Prepare to echo this report
	memcpy(&last_report, ReportData, sizeof(USB_JoystickReport_Input_t));
	echoes = ECHOES;
}