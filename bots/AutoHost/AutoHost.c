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
#include "../Joystick.h"
#include "Commands.h"
#include "Config.h"

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

Command tempCommand;
int durationCount = 0;

// start and end index of "Setup"
int commandIndex = 0;
int m_endIndex = 2;
int m_sequence = 0;
uint8_t currentNumber = 0;

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

		if (m_sequence == 1)	// Raid hosting
		{
			if (m_skip3Days)
			{
				m_sequence = 113;
				return;
			}
			else
			{
				// Connect internet and enter raid
				commandIndex = 3;	// 3 = go online, 8 = local only
				m_endIndex = 14;
			}
		}
		else if (m_sequence == 2)
		{
			if (!m_useLinkCode)
			{
				if (m_alternate) {
					m_useLinkCode = true;
				}
				// Skip to start raid
				m_sequence = 26;
				return;
			}
			else
			{
				if (m_alternate) {
					m_useLinkCode = false;
				}

				// Prepare link code, goto 0
				commandIndex = 27;
				m_endIndex = 34;
			}
		}
		else if (m_sequence >= 3 && m_sequence <= 25)
		{
			// Entering link code
			if (m_sequence % 3 == 0) // 3,6,9,12
			{
				currentNumber = m_useRandomCode ? (rand() % 10) : m_linkCode[m_sequence / 3 - 1];

				if (currentNumber == 0)
				{
					// Just press A for 0
					commandIndex = 35;
					m_endIndex = 36;

					// Skip going down (12 is last input, only skip 1)
					m_sequence += (m_sequence == 24) ? 1 : 2;
				}
				else if (currentNumber % 3 == 0) // 3,6,9
				{
					commandIndex = 45 + (currentNumber / 3 - 1) * 2;
					m_endIndex = 52;
				}
				else // 1,4,7,2,5,8
				{
					commandIndex = 37 + (currentNumber / 3) * 2;
					m_endIndex = (currentNumber % 3 == 1) ? 44 : 42;
				}
			}
			else if (m_sequence % 3 == 1) // 4,7,10,13
			{
				// Press A
				commandIndex = 35;
				m_endIndex = 36;
			}
			else // 5,8,11
			{
				// Reset to 0 (optimized number of down presses)
				commandIndex = 29 + ((currentNumber - 1) / 3) * 2 ;
				m_endIndex = 34;
			}
		}
		else if (m_sequence == 26)
		{
			// Finish setting link code
			commandIndex = 53;
			m_endIndex = 56;
		}
		else if (m_sequence == 27)
		{
			if (m_pokemonIsCatchable)
			{
				return; // just continue the sequence
			}
			else
			{
				// we need one more A press for the extra dialogue on non-catchable mons
				commandIndex = 22;
				m_endIndex = 24;
			}
		}
		else if (m_sequence == 28)
		{
			if (m_addFriends)
			{
				commandIndex = 156;
				m_endIndex = 161;

				// Jump to add friend sequence
				m_sequence = 212;
			}
			else
			{
				// Invite others and wait
				commandIndex = (m_waitTime == 0) ? 15 : 17;
				m_endIndex = commandIndex + 1;
			}
		}
		else if (m_sequence == 29)
		{
			// Host get ready and start raid
			commandIndex = 19;
			m_endIndex = 24;
		}
		else if (m_sequence >= 30 && m_sequence <= 53)
		{
			// A Spam 23 times
			commandIndex = 25;
			m_endIndex = 26;

      if (m_sequence == 53) {
        m_sequence = 69;
      }
		}
		else if (m_sequence == 70)
		{
			if (!m_unsafeDC)
			{
				// Soft reset
				commandIndex = 57;
				m_endIndex = 68;
			}
			else
			{
				// Unsafe DC
				commandIndex = 69;
				m_endIndex = 92;
			}

			m_sequence = 0;
		}
		else if (m_sequence == 114)	// Day skipping
		{
			// Sync and unsync time
			commandIndex = 93;
			m_endIndex = 127;
		}
		else if (m_sequence == 115)
		{
			// Back to game after resetting time
			commandIndex = 140;
			m_endIndex = 143;
		}
		else if (m_sequence == 131)
		{
			// Connect internet and enter raid
			commandIndex = 3;	// 3 = go online, 8 = local only
			m_endIndex = 14;

			m_sequence = 1;
		}
		else if (m_sequence >= 116 && m_sequence <= 130)
		{
			if (m_sequence % 5 == 1)	// 103,108,113
			{
				// Collect watts and invite others
				commandIndex = 148;
				m_endIndex = 155;
			}
			else if (m_sequence % 5 == 2)	// 104,109,114
			{
				// Goto date and time 1
				commandIndex = 93;
				m_endIndex = 123;
			}
			else if (m_sequence % 5 == 3)	// 105,110,115
			{
				// Goto date and time 2
				commandIndex = 128;
				m_endIndex = 131;
			}
			else if (m_sequence % 5 == 4)	// 106,111,116
			{
				// Plus 1 year
				if (m_JP_EU_US == 0)
				{
					commandIndex = 134;
					m_endIndex = 139;
				}
				else
				{
					commandIndex = 132;
					m_endIndex = 139;
				}
			}
			else if (m_sequence % 5 == 0)	// 107,112,117
			{
				// Back to game and quit raid
				commandIndex = 140;
				m_endIndex = 147;
			}
		}
		else if (m_sequence == 213)
		{
			// Goto profile 1 to 10's add friend
			commandIndex = 182 - m_profile * 2;
			m_endIndex = 185;
		}
		else if (m_sequence >= 214 && m_sequence <= 592)
		{
			// Spam A
			commandIndex = 186;
			m_endIndex = 187;

			// Only wait 1 min, skip
			if (m_waitTime == 0 && m_sequence == 381)
			{
				m_sequence = 592;
			}
		}
		else if (m_sequence == 593)
		{
			// Back to game
			commandIndex = 188;
			m_endIndex = 191;

			// Ready and start raid
			m_sequence = 28;
		}
	}

	memcpy_P(&tempCommand, &(m_command[commandIndex]), sizeof(Command));
	switch (tempCommand.button)
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

		case RDOWN:
			ReportData->RY = STICK_MAX;
			break;

		case RIGHT:
			ReportData->LX = STICK_MAX;
			break;

    case UP_A:
      ReportData->LY = STICK_MIN;
      ReportData->Button |= SWITCH_A;
      break;

    case RIGHT_A:
      ReportData->LX = STICK_MAX;
      ReportData->Button |= SWITCH_A;
      break;

    case RLEFT:
      ReportData->RX = STICK_MIN;
      break;

    case RRIGHT:
      ReportData->RX = STICK_MAX;
      break;

		case X:
			ReportData->Button |= SWITCH_X;
			break;

		case Y:
			ReportData->Button |= SWITCH_Y;
			break;

		case A:
			ReportData->Button |= SWITCH_A;
			break;

		case B:
			ReportData->Button |= SWITCH_B;
			break;

		/*case L:
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
			break;*/

		case PLUS:
			ReportData->Button |= SWITCH_PLUS;
			break;

		/*case LCLICK:
			ReportData->Button |= SWITCH_LCLICK;
			break;

		case RCLICK:
			ReportData->Button |= SWITCH_RCLICK;
			break;*/

		case TRIGGERS:
			ReportData->Button |= SWITCH_L | SWITCH_R;
			break;

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

	// Hard-coded overwrite internet wait duration (yes, I don't like this either)
	if (commandIndex == 4)
	{
		tempCommand.duration = m_internetTime;
	} else if (commandIndex == 66 && m_titleScreenBuffer) {
    tempCommand.duration = 1000;
  }

	if (durationCount > tempCommand.duration)
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
